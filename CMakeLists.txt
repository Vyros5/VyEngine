# Minimum Version
cmake_minimum_required(VERSION 3.1...3.15)

# Project Information
project(
    VyEngine 
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)


#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# CMakeLists.txt file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=4.6" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

#===========================================================================================
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#===========================================================================================
# Set Directory Paths

# Source Directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake Linking-Files Directroy
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================

set(sources ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/glad.c)

# set(includes ${SOURCE_DIR})
# Executable File
add_executable(${CMAKE_PROJECT_NAME} ${sources} ${includes})

#===========================================================================================
# Perform Dependency Linkage

# GLFW
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(${CMAKE_PROJECT_NAME} PRIVATE)

# GLAD
# include(${CMAKE_DIR}/LinkGLAD.cmake)
# LinkGLAD(${CMAKE_PROJECT_NAME} PRIVATE)

# OpenGL
# find_package(OpenGL REQUIRED)
# if (OpenGL_FOUND)
#     target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
#     target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
# else()
#     message(FATAL_ERROR "OpenGL was not found on the system")
# endif()

# GLM
# include(${CMAKE_DIR}/LinkGLM.cmake)
# LinkGLM(${CMAKE_PROJECT_NAME} PRIVATE)
add_subdirectory(libraries/)
#===========================================================================================
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE libraries/includes)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad)
# Enable C++17
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


# Set project folders
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})




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


# Set VyEngine as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})


# Filters
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${VyEngine_SOURCES})


# Enable solution folders
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)