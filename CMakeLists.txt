# \CMakeLists.txt
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)


# Project Information
project(
    VyEngine
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)


message(STATUS "\n==========[${PROJECT_NAME} v${PROJECT_VERSION}]==========\n")


# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.\n")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#===========================================================================================

# Directory Paths

# Project Directory
set(VY_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/VyEngine)

# Project Runtime Directory
set(VY_RUNTIME_DIR ${VY_PROJECT_DIR}/runtime)

# VyLib Directory
set(VY_LIB_DIR ${VY_PROJECT_DIR}/libraries)

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake Linking-Files Directroy
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================

# VyEngine Sub-Directory
add_subdirectory(VyEngine)

#===========================================================================================

# Set configuration properties for VyEngine
if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

