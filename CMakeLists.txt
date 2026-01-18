# Top-Level Rayka CMakeLists.txt File
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

#--------------------------------------------------------------------
# Project Info
#--------------------------------------------------------------------
project(Rayka
    VERSION 0.0.0
    HOMEPAGE_URL "https://github.com/trenaud5298/Rayka"
    LANGUAGES CXX
)

# Is Rayka Top Level Project
string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" RAYKA_STANDALONE)

#--------------------------------------------------------------------
# Options
#--------------------------------------------------------------------
# Rayka Build Options
option(RAYKA_BUILD_SHARED "Build dynamic libraries for Rayka" ON)
option(RAYKA_BUILD_STATIC "Build static libraries for Rayka" OFF)

# Rayka General Options
option(RAYKA_BUILD_EXAMPLES "Build the Rayka example programs" ${RAYKA_STANDALONE})
option(RAYKA_BUILD_TESTS "Build the Rayka test programs" ${RAYKA_STANDALONE})
option(RAYKA_BUILD_DOCS "Build the Rayka documentation" ON)
option(RAYKA_INSTALL "Generate installation target" ON)
option(RAYKA_PACKAGING "Generate Packaging Through CPack" OFF)

# Rayka Backend Options
option(RAYKA_BACKEND_CUDA "Build the CUDA backend for Rayka" OFF)
option(RAYKA_BACKEND_OPENGL "Build the OpenGL backend for Rayka" OFF)
option(RAYKA_BACKEND_VULKAN "Build the Vulkan backend for Rayka" OFF)


#--------------------------------------------------------------------
# Create generated files
#--------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(RAYKA_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/Rayka")

configure_package_config_file(
    CMake/RaykaConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/RaykaConfig.cmake
    INSTALL_DESTINATION "${RAYKA_CONFIG_PATH}"
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/RaykaConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

#--------------------------------------------------------------------
# Sub-Directories
#--------------------------------------------------------------------
# Required Core Lib
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Core)

# Optional Backends
if(RAYKA_BACKEND_CUDA)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Backends/CUDA)
endif()

if(RAYKA_BACKEND_OPENGL)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Backends/OpenGL)
endif()

if(RAYKA_BACKEND_VULKAN)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Backends/Vulkan)
endif()

# Examples
if(RAYKA_BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Examples/Core)

    if(RAYKA_BACKEND_CUDA)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Examples/CUDA)
    endif()

    if(RAYKA_BACKEND_OPENGL)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Examples/OpenGL)
    endif()

    if(RAYKA_BACKEND_VULKAN)
        add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Examples/Vulkan)
    endif()
endif()

#--------------------------------------------------------------------
# Install
#--------------------------------------------------------------------
if(RAYKA_INSTALL)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/RaykaInstall.cmake)
endif()

#--------------------------------------------------------------------
# Packaging
#--------------------------------------------------------------------
if(RAYKA_PACKAGING)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/RaykaPackaging.cmake)
endif()