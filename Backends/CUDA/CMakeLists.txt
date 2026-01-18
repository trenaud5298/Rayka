# Rayka::CUDA CMakeLists.txt File

#--------------------------------------------------------------------
# CUDA Setup
#--------------------------------------------------------------------
set(RAYKA_CUDA_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_CUDA_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_CUDA_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# CUDA Dependencies
#--------------------------------------------------------------------
enable_language(CUDA)
find_package(CUDAToolkit REQUIRED)

#--------------------------------------------------------------------
# File Setup
#--------------------------------------------------------------------
# Generated header setup
include(GenerateExportHeader)
set(_rayka_cuda_generated_directory "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(_rayka_cuda_generated_export_header "${CMAKE_CURRENT_BINARY_DIR}/generated/Rayka/CUDA/Export.h")

# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_CUDA_SOURCES CONFIGURE_DEPENDS
    "${RAYKA_CUDA_SOURCE_DIR}/*.cpp"
    "${RAYKA_CUDA_SOURCE_DIR}/*.cu"
)
source_group(TREE ${RAYKA_CUDA_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_CUDA_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_CUDA_HEADERS CONFIGURE_DEPENDS
    "${RAYKA_CUDA_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_CUDA_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_CUDA_HEADERS})

# Add Generated Header To Header List & Add To Source Group
list(APPEND RAYKA_CUDA_HEADERS ${_rayka_cuda_generated_export_header})
source_group("include/Rayka/CUDA" FILES ${_rayka_cuda_generated_export_header})

#--------------------------------------------------------------------
# Create Library
#--------------------------------------------------------------------
set(RAYKA_CUDA_TARGETS)

if(RAYKA_BUILD_SHARED)
    add_library(rayka_cuda SHARED)
    add_library(Rayka::CUDA ALIAS rayka_cuda)
    set_target_properties(rayka_cuda PROPERTIES EXPORT_NAME CUDA)
    list(APPEND RAYKA_CUDA_TARGETS rayka_cuda)
endif()

if(RAYKA_BUILD_STATIC)
    add_library(rayka_cuda_static STATIC)
    add_library(Rayka::CUDA_Static ALIAS rayka_cuda_static)
    set_target_properties(rayka_cuda_static PROPERTIES EXPORT_NAME CUDA_Static)
    target_compile_definitions(rayka_cuda_static PUBLIC RAYKA_CUDA_STATIC_DEFINE)
    list(APPEND RAYKA_CUDA_TARGETS rayka_cuda_static)
endif()

#--------------------------------------------------------------------
# Export Header
#--------------------------------------------------------------------
if(TARGET rayka_cuda)
    set(_rayka_export_header_target rayka_cuda)
elseif(TARGET rayka_cuda_static)
    set(_rayka_export_header_target rayka_cuda_static)
else()
    message(FATAL_ERROR "[Rayka] No Rayka::CUDA target exists to generate export header")
endif()

generate_export_header(${_rayka_export_header_target}
    BASE_NAME RAYKA_CUDA
    EXPORT_FILE_NAME ${_rayka_cuda_generated_export_header}
)

#--------------------------------------------------------------------
# Target Configuration
#--------------------------------------------------------------------
foreach(target ${RAYKA_CUDA_TARGETS})
    target_sources(${target}
        PRIVATE
            ${RAYKA_CUDA_SOURCES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${RAYKA_CUDA_INCLUDE_DIR}
            ${_rayka_cuda_generated_directory}
        FILES
            ${RAYKA_CUDA_HEADERS}
    )

    set(_rayka_core_dep Rayka::Core)
    if(target STREQUAL "rayka_cuda_static")
        set(_rayka_core_dep Rayka::Core_Static)
    endif()

    target_link_libraries(${target}
        PUBLIC
            ${_rayka_core_dep}
        PRIVATE
            CUDA::cudart
    )

    target_include_directories(${target}
        PRIVATE
            ${RAYKA_CUDA_SOURCE_DIR}
        PUBLIC
            $<INSTALL_INTERFACE:include>
    )

    set_target_properties(${target} PROPERTIES
        # C++ Standard
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        # Compiler Options
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        # CUDA Properties
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
    )

    target_compile_features(${target} PUBLIC cxx_std_20)
endforeach()
#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(TARGETS ${RAYKA_CUDA_TARGETS}
    EXPORT RaykaCUDATargets
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT cuda_runtime
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT cuda_runtime
        NAMELINK_COMPONENT cuda_development
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT cuda_development
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT cuda_development
)