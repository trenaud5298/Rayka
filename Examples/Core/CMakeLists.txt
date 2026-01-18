# Rayka::Core Example CMakeLists.txt File

#--------------------------------------------------------------------
# Core Example Setup
#--------------------------------------------------------------------
set(RAYKA_CORE_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RAYKA_CORE_EXAMPLE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(RAYKA_CORE_EXAMPLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

#--------------------------------------------------------------------
# Core Example Dependencies
#--------------------------------------------------------------------
if(NOT TARGET Rayka::Core AND NOT TARGET Rayka::Core_Static)
    message(FATAL_ERROR "[Rayka] Rayka::Core is not defined. Unable to generated example for core module")
endif()


#--------------------------------------------------------------------
# Create Executable
#--------------------------------------------------------------------
add_executable(rayka_core_example)

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------
# Grab Sources & Add Source Group
file(GLOB_RECURSE RAYKA_CORE_EXAMPLE_SOURCES
        CONFIGURE_DEPENDS "${RAYKA_CORE_EXAMPLE_SOURCE_DIR}/*.cpp"
)
source_group(TREE ${RAYKA_CORE_EXAMPLE_SOURCE_DIR} PREFIX "src" FILES ${RAYKA_CORE_EXAMPLE_SOURCES})

# Grab Headers & Add Source Group
file(GLOB_RECURSE RAYKA_CORE_EXAMPLE_HEADERS
        CONFIGURE_DEPENDS "${RAYKA_CORE_EXAMPLE_INCLUDE_DIR}/*.h"
)
source_group(TREE ${RAYKA_CORE_EXAMPLE_INCLUDE_DIR} PREFIX "include" FILES ${RAYKA_CORE_EXAMPLE_HEADERS})


# Add Sources To Target
target_sources(rayka_core_example
    PRIVATE
        ${RAYKA_CORE_EXAMPLE_SOURCES}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            ${RAYKA_CORE_EXAMPLE_INCLUDE_DIR}
        FILES
            ${RAYKA_CORE_EXAMPLE_HEADERS}
)

#--------------------------------------------------------------------
# Additional Target Configuration
#--------------------------------------------------------------------
set(_rayka_core_dep Rayka::Core)
if(NOT TARGET Rayka::Core)
    set(_rayka_core_dep Rayka::Core_Static)
endif()
target_link_libraries(rayka_core_example
    PRIVATE
        ${_rayka_core_dep}
)

target_include_directories(rayka_core_example
    PRIVATE
        ${RAYKA_CORE_EXAMPLE_SOURCE_DIR}
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

set_target_properties(rayka_core_example PROPERTIES
    # C++ Standard
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#--------------------------------------------------------------------
# Target Install
#--------------------------------------------------------------------
install(
    TARGETS rayka_core_example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT core_example
)