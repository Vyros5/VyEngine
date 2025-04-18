# \CMakeLists.txt
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)


# Project Information
project(
    VyEngine
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)

# Properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "\n==========[${PROJECT_NAME} v${PROJECT_VERSION}]==========\n")


# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.\n")
endif()

option(BUILD_SANDBOX "build sandbox projects" ON)
#===========================================================================================

# Directory Paths

# VyEngine Directory
set(VY_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/VyEngine)

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake Linking-Files Directroy
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================

# VyEngine Sub-Directory
add_subdirectory(VyEngine)

add_executable(VyEngine ${VY_ENGINE_DIR}/src/core/main.cpp)

target_link_libraries(VyEngine PRIVATE VyEngineSrc)



#===========================================================================================

# if (BUILD_SANDBOX)
# add_subdirectory(sample/Sandbox)
# set(STARTUP_PROJECT_NAME "Sandbox")
# endif()

#===========================================================================================

# # Set configuration properties for VyEngine
# if(MSVC)
#     message(STATUS "[MSVC]")
#     target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
#         /W3
#         /MP # multithreaded build
#         /WX # warnings as errors
#         /ZI # program database for edit and continue
#     )
# else()
#     target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE 
#         -Wall 
#         -Wextra 
#         -Wpedantic
#     )
# endif()

