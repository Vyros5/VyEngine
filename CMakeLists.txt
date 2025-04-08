# VyEngine\CMakeLists.txt
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)


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

#===========================================================================================
# Directory Paths

# Project Directory
set(VY_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/VyEngine)

# Project Source Directory
set(VY_SOURCE_DIR ${VY_PROJECT_DIR}/src)

# Project Includes Directory
set(VY_INCLUDE_DIR ${VY_PROJECT_DIR}/include)

#VyLib Directory
set(VY_LIB_DIR ${VY_PROJECT_DIR}/libraries)

# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake Linking-Files Directroy
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================



# VyEngine Sub-Directory
add_subdirectory(VyEngine)


#===========================================================================================
# Dependency Linkage

# GLFW
# include(${CMAKE_DIR}/LinkGLFW.cmake)
# LinkGLFW(${CMAKE_PROJECT_NAME} PRIVATE)


# # GLAD
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/VyEngine/libraries/glad)


# # OpenGL
# include(${CMAKE_DIR}/LinkOpenGL.cmake)
# LinkOpenGL(${CMAKE_PROJECT_NAME} PRIVATE)

# find_package(OpenGL REQUIRED)
# if (OpenGL_FOUND)
#     message(STATUS "[OpenGL]: Libararies - ${OPENGL_LIBRARIES}\n")
#     target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
#     target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
# else()
#     message(FATAL_ERROR "OpenGL was not found on the system.\n")
# endif()


# GLM
# include(${CMAKE_DIR}/LinkGLM.cmake)
# LinkGLM(${CMAKE_PROJECT_NAME} PRIVATE)


#===========================================================================================

# target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
#     ${VY_INCLUDE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/libraries
# )

# # 3rd Party Libraries Directory
# target_link_libraries(${CMAKE_PROJECT_NAME} 
#     PRIVATE
#         glad

# )

#===========================================================================================

# Set project folders
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})


# Set configuration properties for VyEngine
if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        /W3
        /MP # multithreaded build
        # /WX # warnings as errors
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