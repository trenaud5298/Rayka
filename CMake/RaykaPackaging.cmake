# cmake/RaykaPackaging.cmake
# Handles All CPack Logic

# Requires Install Setup
if(NOT RAYKA_INSTALL)
    message(FATAL_ERROR "[Rayka] Packaging support (RAYKA_PACKAGING) requires installation rules enabled (RAYKA_INSTALL)")
endif()

# Basic config
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Tyler Renaud")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} - A ray tracing library designed to make rendering simple scenes fast and easy.")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "trenaud_5298@email.ric.edu")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")

# Set packaging name to <name>-<version>-<system>
if(NOT CPACK_PACKAGE_FILE_NAME)
    string(TOLOWER "${CMAKE_SYSTEM_NAME}" _cpack_system)
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${_cpack_system}")
endif()

# Add LICENSE and README
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

# Shared Generator
set(CPACK_GENERATOR "ZIP")

# Windows Specific Logic
if(WIN32)
    # Installer Setup
    list(APPEND CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME} ${PROJECT_VERSION}")
    set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
    set(CPACK_NSIS_MODIFY_PATH OFF)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_COMPONENT_INSTALL ON)

    # LICENSE Formatting Correction On Windows
    set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/cmake/LICENSE.rtf)
endif()

# UNIX (Non Apple) Specific Logic
if(UNIX AND NOT APPLE)
    list(APPEND CPACK_GENERATOR "TGZ")
endif()

include(CPackComponent)

#--------------------------------------------------------------------
# Components
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# Install Types
#--------------------------------------------------------------------
cpack_add_install_type(Runtime DISPLAY_NAME "Runtime Install")
cpack_add_install_type(Development DISPLAY_NAME "Development Install" DEFAULT)
cpack_add_install_type(Full DISPLAY_NAME "Full Install")

#--------------------------------------------------------------------
# Component Groups
#--------------------------------------------------------------------
cpack_add_component_group(runtime
    DISPLAY_NAME "Runtime"
    DESCRIPTION "Runtime components for Rayka"
    BOLD_TITLE
)

cpack_add_component_group(development
    DISPLAY_NAME "Development"
    DESCRIPTION "Development files for Rayka (headers, CMake targets, static libs)"
    BOLD_TITLE
)

cpack_add_component_group(examples
    DISPLAY_NAME "Examples"
    DESCRIPTION "Example applications demonstrating Rayka usage"
    BOLD_TITLE
)

cpack_add_component_group(runtime_backends
    DISPLAY_NAME "Backends"
    DESCRIPTION "Runtime components for optional Rayka GPU backends"
    PARENT_GROUP runtime
)

cpack_add_component_group(development_backends
    DISPLAY_NAME "Backends"
    DESCRIPTION "Development files for optional Rayka GPU backends"
    PARENT_GROUP development
)

#--------------------------------------------------------------------
# Runtime Components
#--------------------------------------------------------------------
if(RAYKA_BUILD_SHARED)
    cpack_add_component(core_runtime
        GROUP runtime
        DESCRIPTION "Core runtime for Rayka"
        INSTALL_TYPES Runtime Development Full
    )
    # Runtime Backend Components
    if(RAYKA_BACKEND_CUDA)
        cpack_add_component(cuda_runtime
            GROUP runtime_backends
            DESCRIPTION "Optional CUDA backend runtime for Rayka"
            INSTALL_TYPES Runtime Development Full
            DEPENDS core_runtime
        )
    endif()
    if(RAYKA_BACKEND_OPENGL)
        cpack_add_component(opengl_runtime
            GROUP runtime_backends
            DESCRIPTION "Optional OpenGL backend runtime for Rayka"
            INSTALL_TYPES Runtime Development Full
            DEPENDS core_runtime
        )
    endif()
    if(RAYKA_BACKEND_VULKAN)
        cpack_add_component(vulkan_runtime
            GROUP runtime_backends
            DESCRIPTION "Optional Vulkan backend runtime for Rayka"
            INSTALL_TYPES Runtime Development Full
            DEPENDS core_runtime
        )
    endif()
endif()

#--------------------------------------------------------------------
# Development Components
#--------------------------------------------------------------------
cpack_add_component(core_development
    GROUP development
    DESCRIPTION "Core development files for Rayka"
    INSTALL_TYPES Development Full
)
# Development Backend Components
if(RAYKA_BACKEND_CUDA)
    cpack_add_component(cuda_development
        GROUP development_backends
        DESCRIPTION "Optional CUDA backend development files for Rayka"
        INSTALL_TYPES Development Full
        DEPENDS core_development
    )
endif()
if(RAYKA_BACKEND_OPENGL)
    cpack_add_component(opengl_development
        GROUP development_backends
        DESCRIPTION "Optional OpenGL backend development files for Rayka"
        INSTALL_TYPES Development Full
        DEPENDS core_development
    )
endif()
if(RAYKA_BACKEND_VULKAN)
    cpack_add_component(vulkan_development
        GROUP development_backends
        DESCRIPTION "Optional Vulkan backend development files for Rayka"
        INSTALL_TYPES Development Full
        DEPENDS core_development
    )
endif()

#--------------------------------------------------------------------
# Example Components
#--------------------------------------------------------------------
if(RAYKA_BUILD_EXAMPLES)
    set(_rayka_example_dep "runtime")
    if(NOT RAYKA_BUILD_SHARED)
        set(_rayka_example_dep "development")
    endif()

    cpack_add_component(core_example
        GROUP examples
        DESCRIPTION "Example of Rayka's core library"
        INSTALL_TYPES Full
        DEPENDS core_${_rayka_example_dep}
    )
    # Example Backend Components
    if(RAYKA_BACKEND_CUDA)
        cpack_add_component(cuda_example
            GROUP examples
            DESCRIPTION "Example of Rayka's optional CUDA backend"
            INSTALL_TYPES Full
            DEPENDS cuda_${_rayka_example_dep}
        )
    endif()
    if(RAYKA_BACKEND_OPENGL)
        cpack_add_component(opengl_example
            GROUP examples
            DESCRIPTION "Example of Rayka's optional OpenGL backend"
            INSTALL_TYPES Full
            DEPENDS opengl_${_rayka_example_dep}
        )
    endif()
    if(RAYKA_BACKEND_VULKAN)
        cpack_add_component(vulkan_example
            GROUP examples
            DESCRIPTION "Example of Rayka's optional Vulkan backend"
            INSTALL_TYPES Full
            DEPENDS vulkan_${_rayka_example_dep}
        )
    endif()
endif()
include(CPack)

message(STATUS "=== CPack Components ===")
foreach(c ${CPACK_COMPONENTS_ALL})
    message(STATUS "Component: ${c}")
endforeach()
