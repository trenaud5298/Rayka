# Rayka::Vulkan Example CMakeLists.txt File

#--------------------------------------------------------------------
# Vulkan Example Setup
#--------------------------------------------------------------------
set(RAYKA_VULKAN_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_VULKAN_EXAMPLE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_VULKAN_EXAMPLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# Vulkan Example Dependencies
#--------------------------------------------------------------------
if(NOT TARGET Rayka::Vulkan AND NOT TARGET Rayka::Vulkan_Static)
    message(FATAL_ERROR "[Rayka] Rayka::Vulkan is not defined. Unable to generated example for vulkan module")
endif()


#--------------------------------------------------------------------
# Create Executable
#--------------------------------------------------------------------
add_executable(rayka_vulkan_example)

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------
# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_VULKAN_EXAMPLE_SOURCES
        CONFIGURE_DEPENDS "${RAYKA_VULKAN_EXAMPLE_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_VULKAN_EXAMPLE_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_VULKAN_EXAMPLE_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_VULKAN_EXAMPLE_HEADERS
        CONFIGURE_DEPENDS "${RAYKA_VULKAN_EXAMPLE_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_VULKAN_EXAMPLE_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_VULKAN_EXAMPLE_HEADERS})


# Add Sources To Target
target_sources(rayka_vulkan_example
    PRIVATE
        ${RAYKA_VULKAN_EXAMPLE_SOURCES}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${RAYKA_VULKAN_EXAMPLE_INCLUDE_DIR}
        FILES
            ${RAYKA_VULKAN_EXAMPLE_HEADERS}
)

#--------------------------------------------------------------------
# Additional Target Configuration
#--------------------------------------------------------------------
set(_rayka_vulkan_dep Rayka::Vulkan)
if(NOT TARGET Rayka::Vulkan)
    set(_rayka_vulkan_dep Rayka::Vulkan_Static)
endif()
target_link_libraries(rayka_vulkan_example
    PRIVATE
        ${_rayka_vulkan_dep}
)

target_include_directories(rayka_vulkan_example
    PRIVATE
        ${RAYKA_VULKAN_EXAMPLE_SOURCE_DIR}
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

set_target_properties(rayka_vulkan_example PROPERTIES
    # C++ Standard
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(
    TARGETS rayka_vulkan_example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT vulkan_example
)