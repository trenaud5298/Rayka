# Rayka::OpenGL CMakeLists.txt File

#--------------------------------------------------------------------
# OpenGL Setup
#--------------------------------------------------------------------
set(RAYKA_OPENGL_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_OPENGL_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_OPENGL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# OpenGL Dependencies
#--------------------------------------------------------------------
# Will be added later in development

#--------------------------------------------------------------------
# File Setup
#--------------------------------------------------------------------
# Generated header setup
include(GenerateExportHeader)
set(_rayka_opengl_generated_directory "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(_rayka_opengl_generated_export_header "${CMAKE_CURRENT_BINARY_DIR}/generated/Rayka/OpenGL/Export.h")

# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_OPENGL_SOURCES CONFIGURE_DEPENDS
    "${RAYKA_OPENGL_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_OPENGL_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_OPENGL_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_OPENGL_HEADERS CONFIGURE_DEPENDS
    "${RAYKA_OPENGL_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_OPENGL_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_OPENGL_HEADERS})

# Add Generated Header To Header List & Add To Source Group
list(APPEND RAYKA_OPENGL_HEADERS ${_rayka_opengl_generated_export_header})
source_group("include/Rayka/OpenGL" FILES ${_rayka_opengl_generated_export_header})

#--------------------------------------------------------------------
# Create Library
#--------------------------------------------------------------------
set(RAYKA_OPENGL_TARGETS)

if(RAYKA_BUILD_SHARED)
    add_library(rayka_opengl SHARED)
    add_library(Rayka::OpenGL ALIAS rayka_opengl)
    set_target_properties(rayka_opengl PROPERTIES EXPORT_NAME OpenGL)
    list(APPEND RAYKA_OPENGL_TARGETS rayka_opengl)
endif()

if(RAYKA_BUILD_STATIC)
    add_library(rayka_opengl_static STATIC)
    add_library(Rayka::OpenGL_Static ALIAS rayka_opengl_static)
    set_target_properties(rayka_opengl_static PROPERTIES EXPORT_NAME OpenGL_Static)
    target_compile_definitions(rayka_opengl_static PUBLIC RAYKA_OPENGL_STATIC_DEFINE)
    list(APPEND RAYKA_OPENGL_TARGETS rayka_opengl_static)
endif()

#--------------------------------------------------------------------
# Export Header
#--------------------------------------------------------------------
if(TARGET rayka_opengl)
    set(_rayka_export_header_target rayka_opengl)
elseif(TARGET rayka_opengl_static)
    set(_rayka_export_header_target rayka_opengl_static)
else()
    message(FATAL_ERROR "[Rayka] No Rayka::OpenGL target exists to generate export header")
endif()

generate_export_header(${_rayka_export_header_target}
    BASE_NAME RAYKA_OPENGL
    EXPORT_FILE_NAME ${_rayka_opengl_generated_export_header}
)

#--------------------------------------------------------------------
# Target Configuration
#--------------------------------------------------------------------
foreach(target ${RAYKA_OPENGL_TARGETS})
    target_sources(${target}
        PRIVATE
            ${RAYKA_OPENGL_SOURCES}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${RAYKA_OPENGL_INCLUDE_DIR}
                ${_rayka_opengl_generated_directory}
            FILES
                ${RAYKA_OPENGL_HEADERS}
    )

    set(_rayka_core_dep Rayka::Core)
    if(target STREQUAL "rayka_opengl_static")
        set(_rayka_core_dep Rayka::Core_Static)
    endif()

    target_link_libraries(${target}
        PUBLIC
            ${_rayka_core_dep}
    )

    target_include_directories(${target}
        PRIVATE
            ${RAYKA_OPENGL_SOURCE_DIR}
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
install(TARGETS ${RAYKA_OPENGL_TARGETS}
    EXPORT RaykaOpenGLTargets
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT opengl_runtime
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT opengl_runtime
        NAMELINK_COMPONENT opengl_development
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT opengl_development
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT opengl_development
)