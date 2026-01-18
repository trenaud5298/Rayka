# Rayka::CUDA Example CMakeLists.txt File

#--------------------------------------------------------------------
# CUDA Example Setup
#--------------------------------------------------------------------
set(RAYKA_CUDA_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_CUDA_EXAMPLE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_CUDA_EXAMPLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# CUDA Example Dependencies
#--------------------------------------------------------------------
if(NOT TARGET Rayka::CUDA AND NOT TARGET Rayka::CUDA_Static)
    message(FATAL_ERROR "[Rayka] Rayka::CUDA is not defined. Unable to generated example for cuda module")
endif()


#--------------------------------------------------------------------
# Create Executable
#--------------------------------------------------------------------
add_executable(rayka_cuda_example)

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------
# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_CUDA_EXAMPLE_SOURCES
        CONFIGURE_DEPENDS "${RAYKA_CUDA_EXAMPLE_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_CUDA_EXAMPLE_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_CUDA_EXAMPLE_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_CUDA_EXAMPLE_HEADERS
        CONFIGURE_DEPENDS "${RAYKA_CUDA_EXAMPLE_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_CUDA_EXAMPLE_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_CUDA_EXAMPLE_HEADERS})


# Add Sources To Target
target_sources(rayka_cuda_example
    PRIVATE
        ${RAYKA_CUDA_EXAMPLE_SOURCES}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${RAYKA_CUDA_EXAMPLE_INCLUDE_DIR}
        FILES
            ${RAYKA_CUDA_EXAMPLE_HEADERS}
)

#--------------------------------------------------------------------
# Additional Target Configuration
#--------------------------------------------------------------------
set(_rayka_cuda_dep Rayka::CUDA)
if(NOT TARGET Rayka::CUDA)
    set(_rayka_cuda_dep Rayka::CUDA_Static)
endif()
target_link_libraries(rayka_cuda_example
    PRIVATE
        ${_rayka_cuda_dep}
)

target_include_directories(rayka_cuda_example
    PRIVATE
        ${RAYKA_CUDA_EXAMPLE_SOURCE_DIR}
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

set_target_properties(rayka_cuda_example PROPERTIES
    # C++ Standard
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(
    TARGETS rayka_cuda_example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT cuda_example
)
