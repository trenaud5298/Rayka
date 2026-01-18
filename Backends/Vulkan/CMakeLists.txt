# Rayka::Vulkan CMakeLists.txt File

#--------------------------------------------------------------------
# Vulkan Setup
#--------------------------------------------------------------------
set(RAYKA_VULKAN_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_VULKAN_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_VULKAN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# Vulkan Dependencies
#--------------------------------------------------------------------
# Will be added later in development

#--------------------------------------------------------------------
# File Setup
#--------------------------------------------------------------------
# Generated header setup
include(GenerateExportHeader)
set(_rayka_vulkan_generated_directory "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(_rayka_vulkan_generated_export_header "${CMAKE_CURRENT_BINARY_DIR}/generated/Rayka/Vulkan/Export.h")

# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_VULKAN_SOURCES CONFIGURE_DEPENDS
    "${RAYKA_VULKAN_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_VULKAN_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_VULKAN_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_VULKAN_HEADERS CONFIGURE_DEPENDS
    "${RAYKA_VULKAN_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_VULKAN_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_VULKAN_HEADERS})

# Add Generated Header To Header List & Add To Source Group
list(APPEND RAYKA_VULKAN_HEADERS ${_rayka_vulkan_generated_export_header})
source_group("include/Rayka/Vulkan" FILES ${_rayka_vulkan_generated_export_header})

#--------------------------------------------------------------------
# Create Library
#--------------------------------------------------------------------
set(RAYKA_VULKAN_TARGETS)

if(RAYKA_BUILD_SHARED)
    add_library(rayka_vulkan SHARED)
    add_library(Rayka::Vulkan ALIAS rayka_vulkan)
    set_target_properties(rayka_vulkan PROPERTIES EXPORT_NAME Vulkan)
    list(APPEND RAYKA_VULKAN_TARGETS rayka_vulkan)
endif()

if(RAYKA_BUILD_STATIC)
    add_library(rayka_vulkan_static STATIC)
    add_library(Rayka::Vulkan_Static ALIAS rayka_vulkan_static)
    set_target_properties(rayka_vulkan_static PROPERTIES EXPORT_NAME Vulkan_Static)
    target_compile_definitions(rayka_vulkan_static PUBLIC RAYKA_VULKAN_STATIC_DEFINE)
    list(APPEND RAYKA_VULKAN_TARGETS rayka_vulkan_static)
endif()

#--------------------------------------------------------------------
# Export Header
#--------------------------------------------------------------------
if(TARGET rayka_vulkan)
    set(_rayka_export_header_target rayka_vulkan)
elseif(TARGET rayka_vulkan_static)
    set(_rayka_export_header_target rayka_vulkan_static)
else()
    message(FATAL_ERROR "[Rayka] No Rayka::Vulkan target exists to generate export header")
endif()

generate_export_header(${_rayka_export_header_target}
    BASE_NAME RAYKA_VULKAN
    EXPORT_FILE_NAME ${_rayka_vulkan_generated_export_header}
)

#--------------------------------------------------------------------
# Target Configuration
#--------------------------------------------------------------------
foreach(target ${RAYKA_VULKAN_TARGETS})
    target_sources(${target}
        PRIVATE
            ${RAYKA_VULKAN_SOURCES}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${RAYKA_VULKAN_INCLUDE_DIR}
                ${_rayka_vulkan_generated_directory}
            FILES
                ${RAYKA_VULKAN_HEADERS}
    )

    set(_rayka_core_dep Rayka::Core)
    if(target STREQUAL "rayka_vulkan_static")
        set(_rayka_core_dep Rayka::Core_Static)
    endif()

    target_link_libraries(${target}
        PUBLIC
            ${_rayka_core_dep}
    )

    target_include_directories(${target}
        PRIVATE
            ${RAYKA_VULKAN_SOURCE_DIR}
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
install(TARGETS ${RAYKA_VULKAN_TARGETS}
    EXPORT RaykaVulkanTargets
        RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT vulkan_runtime
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT vulkan_runtime
        NAMELINK_COMPONENT vulkan_development
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT vulkan_development
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT vulkan_development
)