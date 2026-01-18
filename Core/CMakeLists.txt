# Rayka::Core CMakeLists.txt File

#--------------------------------------------------------------------
# Core Setup
#--------------------------------------------------------------------
set(RAYKA_CORE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_CORE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_CORE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# Core Dependencies
#--------------------------------------------------------------------
# No Explicit Dependencies

#--------------------------------------------------------------------
# File Setup
#--------------------------------------------------------------------
# Generated header setup
include(GenerateExportHeader)
set(_rayka_core_generated_directory "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(_rayka_core_generated_export_header "${CMAKE_CURRENT_BINARY_DIR}/generated/Rayka/Core/Export.h")

# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_CORE_SOURCES
        CONFIGURE_DEPENDS "${RAYKA_CORE_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_CORE_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_CORE_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_CORE_HEADERS
        CONFIGURE_DEPENDS "${RAYKA_CORE_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_CORE_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_CORE_HEADERS})

# Add Generated Header To Header List & Add To Source Group
list(APPEND RAYKA_CORE_HEADERS ${_rayka_core_generated_export_header})
source_group("include/Rayka/Core" FILES ${_rayka_core_generated_export_header})

#--------------------------------------------------------------------
# Create Library
#--------------------------------------------------------------------
set(RAYKA_CORE_TARGETS)

message(STATUS "RAYKA_BUILD_SHARED: ${RAYKA_BUILD_SHARED}")
message(STATUS "RAYKA_BUILD_STATIC: ${RAYKA_BUILD_STATIC}")

if(RAYKA_BUILD_SHARED)
    add_library(rayka_core SHARED)
    add_library(Rayka::Core ALIAS rayka_core)
    set_target_properties(rayka_core PROPERTIES EXPORT_NAME Core)
    list(APPEND RAYKA_CORE_TARGETS rayka_core)
endif()

if(RAYKA_BUILD_STATIC)
    add_library(rayka_core_static STATIC)
    add_library(Rayka::Core_Static ALIAS rayka_core_static)
    set_target_properties(rayka_core_static PROPERTIES EXPORT_NAME Core_Static)
    target_compile_definitions(rayka_core_static PUBLIC RAYKA_CORE_STATIC_DEFINE)
    list(APPEND RAYKA_CORE_TARGETS rayka_core_static)
endif()
message(STATUS "CORE LIBS: ${RAYKA_CORE_TARGETS}")
#--------------------------------------------------------------------
# Export Header
#--------------------------------------------------------------------
if(TARGET rayka_core)
    set(_rayka_export_header_target rayka_core)
elseif(TARGET rayka_core_static)
    set(_rayka_export_header_target rayka_core_static)
else()
    message(FATAL_ERROR "[Rayka] No Rayka::Core target exists to generate export header")
endif()

generate_export_header(${_rayka_export_header_target}
    BASE_NAME RAYKA_CORE
    EXPORT_FILE_NAME ${_rayka_core_generated_export_header}
)

#--------------------------------------------------------------------
# Target Configuration
#--------------------------------------------------------------------
foreach(target ${RAYKA_CORE_TARGETS})
    target_sources(${target}
        PRIVATE
            ${RAYKA_CORE_SOURCES}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${RAYKA_CORE_INCLUDE_DIR}
                ${_rayka_core_generated_directory}
            FILES
                ${RAYKA_CORE_HEADERS}
    )

    target_include_directories(${target}
        PRIVATE
            ${RAYKA_CORE_SOURCE_DIR}
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
    )

    target_compile_features(${target} PUBLIC cxx_std_20)
endforeach()
#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(TARGETS ${RAYKA_CORE_TARGETS}
    EXPORT RaykaCoreTargets
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT core_runtime
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT core_runtime
        NAMELINK_COMPONENT core_development
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT core_development
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT core_development
)

