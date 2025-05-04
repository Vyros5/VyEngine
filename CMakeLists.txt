cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
    VyEngineCore
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)

# Properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#==================================================================================================
message(STATUS "\n==========[${PROJECT_NAME} v${PROJECT_VERSION}]==========\n")

# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.\n")
endif()
#==================================================================================================

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#==================================================================================================

add_subdirectory(Source)

#==================================================================================================