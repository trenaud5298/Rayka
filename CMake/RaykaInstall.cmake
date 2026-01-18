# RaykaInstall.cmake
# Handle Install Export Logic

# Core Lib
install(
    EXPORT RaykaCoreTargets
    FILE RaykaCoreTargets.cmake
    NAMESPACE Rayka::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Rayka
    COMPONENT core_development
)

install(
    FILES
        ${PROJECT_SOURCE_DIR}/LICENSE
        ${PROJECT_SOURCE_DIR}/README.md
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT core_development
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/RaykaConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/RaykaConfigVersion.cmake
    DESTINATION ${RAYKA_CONFIG_PATH}
    COMPONENT core_development
)

if(RAYKA_BACKEND_CUDA)
    install(
        EXPORT RaykaCUDATargets
        FILE RaykaCUDATargets.cmake
        NAMESPACE Rayka::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Rayka
        COMPONENT cuda_development
    )
endif()

if(RAYKA_BACKEND_OPENGL)
    install(
        EXPORT RaykaOpenGLTargets
        FILE RaykaOpenGLTargets.cmake
        NAMESPACE Rayka::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Rayka
        COMPONENT opengl_development
    )
endif()

if(RAYKA_BACKEND_VULKAN)
    install(
        EXPORT RaykaVulkanTargets
        FILE RaykaVulkanTargets.cmake
        NAMESPACE Rayka::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Rayka
        COMPONENT vulkan_development
    )
endif()