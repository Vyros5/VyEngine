# Minimum Version
cmake_minimum_required(VERSION 3.30)

# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#     CACHE STRING "Vcpkg toolchain file")

# Project Information
project(
    VyEngine 
    VERSION 0.1.0
    DESCRIPTION "OpenGL 3D Engine" 
    LANGUAGES CXX C
)


# C++ Version
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# Dependencies



# Executable File
add_executable("${CMAKE_PROJECT_NAME}"
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)






# VyEngine include dirs (Header Files)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Automatically links to these libs
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    # glfw
    # glad
    # glm::glm-header-only
)


# Add directories with any random loose .dlls or .libs here
target_link_directories("${CMAKE_PROJECT_NAME}" PRIVATE

)


# Set configuration properties for VyEngine
if(MSVC)
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()


# Set VyEngine as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${CMAKE_PROJECT_NAME}")


# Filters
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${VyEngine_SOURCES})


# Enable solution folders
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)