# VyEngine\CMakeLists.txt
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)


# Project Information
project(
    VyEngine
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)


message(STATUS "==========[${PROJECT_NAME} v${PROJECT_VERSION}]==========\n")


# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed.\n")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#===========================================================================================

#===========================================================================================
# Directory Paths

# Project Directory
set(VY_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/VyEngine)

# Project Source Directory
set(VY_SOURCE_DIR ${VY_PROJECT_DIR}/src)

# Project Includes Directory
set(VY_INCLUDE_DIR ${VY_PROJECT_DIR}/include)

#VyLib Directory
set(VYLIB_DIR ${VY_PROJECT_DIR}/VyLib)

# Main Library Directory
set(MAIN_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake Linking-Files Directroy
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================

# Sources
# file(GLOB_RECURSE VY_SOURCES CONFIGURE_DEPENDS
#     ${VY_SOURCE_DIR}/*.cpp
#     ${VY_SOURCE_DIR}/core/*.cpp
#     ${VY_SOURCE_DIR}/io/camera.cpp
# )

# # Headers
# file(GLOB_RECURSE VY_HEADERS CONFIGURE_DEPENDS
#     ${VY_INCLUDE_DIR}/*.hpp
#     ${VY_INCLUDE_DIR}/core/*.hpp
#     ${VY_INCLUDE_DIR}/io/camera.hpp
# )

# Appliation
add_executable(${CMAKE_PROJECT_NAME} ${VY_SOURCE_DIR}/core/main.cpp) # ${VY_SOURCES} ${VY_HEADERS})



# Properties
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# add_library(VySources ${CMAKE_SOURCE_DIR}/VyEngine/src/core/main.cpp)
# VyEngine Sub-Directory
add_subdirectory(VyEngine)
target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE
    VySources
)

#===========================================================================================
# Dependency Linkage

# GLFW
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(${CMAKE_PROJECT_NAME} PRIVATE)

# GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libraries/glad)
# include(${CMAKE_DIR}/LinkGLAD.cmake)
# LinkGLAD(${CMAKE_PROJECT_NAME} PRIVATE)

# OpenGL
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    message(STATUS "[OpenGL]: Libararies - ${OPENGL_LIBRARIES}")
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

# GLM
include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(${CMAKE_PROJECT_NAME} PRIVATE)


#===========================================================================================
# Main Library Sub-Directory
# target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${MAIN_LIB_DIR})
# add_library(VySources ${CMAKE_CURRENT_SOURCE_DIR}/VyEngine/src/core/main.cpp)
# # VyEngine Sub-Directory
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/VyEngine)


target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    ${VY_INCLUDE_DIR}
    ${VY_INCLUDE_DIR}/core/
)

# 3rd Party Libraries Directory
target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE
        glad
)

#===========================================================================================

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