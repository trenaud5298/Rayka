# Rayka::OpenGL Example CMakeLists.txt File

#--------------------------------------------------------------------
# OpenGL Example Setup
#--------------------------------------------------------------------
set(RAYKA_OPENGL_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_OPENGL_EXAMPLE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_OPENGL_EXAMPLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# OpenGL Example Dependencies
#--------------------------------------------------------------------
if(NOT TARGET Rayka::OpenGL AND NOT TARGET Rayka::OpenGL_Static)
    message(FATAL_ERROR "[Rayka] Rayka::OpenGL is not defined. Unable to generated example for opengl module")
endif()


#--------------------------------------------------------------------
# Create Executable
#--------------------------------------------------------------------
add_executable(rayka_opengl_example)

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------
# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_OPENGL_EXAMPLE_SOURCES
    CONFIGURE_DEPENDS "${RAYKA_OPENGL_EXAMPLE_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_OPENGL_EXAMPLE_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_OPENGL_EXAMPLE_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_OPENGL_EXAMPLE_HEADERS
    CONFIGURE_DEPENDS "${RAYKA_OPENGL_EXAMPLE_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_OPENGL_EXAMPLE_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_OPENGL_EXAMPLE_HEADERS})


# Add Sources To Target
target_sources(rayka_opengl_example
    PRIVATE
        ${RAYKA_OPENGL_EXAMPLE_SOURCES}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${RAYKA_OPENGL_EXAMPLE_INCLUDE_DIR}
        FILES
            ${RAYKA_OPENGL_EXAMPLE_HEADERS}
)

#--------------------------------------------------------------------
# Additional Target Configuration
#--------------------------------------------------------------------
set(_rayka_opengl_dep Rayka::OpenGL)
if(NOT TARGET Rayka::OpenGL)
    set(_rayka_opengl_dep Rayka::OpenGL_Static)
endif()
target_link_libraries(rayka_opengl_example
    PRIVATE
        ${_rayka_opengl_dep}
)

target_include_directories(rayka_opengl_example
    PRIVATE
        ${RAYKA_OPENGL_EXAMPLE_SOURCE_DIR}
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

set_target_properties(rayka_opengl_example PROPERTIES
    # C++ Standard
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(
    TARGETS rayka_opengl_example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT opengl_example
)