# VyEngine\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html


# Appliation
add_executable(${CMAKE_PROJECT_NAME} ${VY_SOURCE_DIR}/main.cpp)
message(STATUS "${CMAKE_PROJECT_NAME}")

# Properties
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Import Third-Party Libraries
add_subdirectory(libraries)


# VyEngine Source Files
set(VY_CORE_SOURCES
    src/main.cpp
    src/window.cpp
)

set(VY_IO_SOURCES
    src/camera.cpp
    src/input.cpp
)

set(VY_LIB_SOURCES
    src/vy_glfw.cpp
    src/vy_file.cpp
)

set(VY_REND_SOURCES
    src/texture.cpp
    src/mesh.cpp
    src/shader.cpp
    src/shader_program.cpp
)

set(VY_COMPILE_HEADERS
    src/vertex_memory.hpp
)

set(VY_HEADERS
    include/window.hpp

    include/camera.hpp
    include/input.hpp

    include/vy_glfw.hpp
    include/vy_file.hpp

    include/texture.hpp
    include/mesh.hpp
    include/shader.hpp
    include/shader_program.hpp
)

# Source file paths should be converted to absolute paths.
cmake_policy(SET CMP0076 NEW)

# Add sources to target.
target_sources(${CMAKE_PROJECT_NAME}  
    PRIVATE 
        ${VY_CORE_SOURCES}
        ${VY_IO_SOURCES}
        ${VY_LIB_SOURCES}
        ${VY_REND_SOURCES}

        ${VY_COMPILE_HEADERS}

    PUBLIC
        ${VY_HEADERS}
)

# Add Include-Libraries to target.
target_include_directories(${CMAKE_PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries
    PRIVATE
        ${assimp_SOURCE_DIR}/include
        ${glad_SOURCE_DIR}/include
        ${glfw_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
        ${stb_SOURCE_DIR}
)

# Link Libaries to project.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    glfw
    glad
    assimp
    stb
)

get_target_property(OUT ${CMAKE_PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "\n[${CMAKE_PROJECT_NAME} Libraries]: ${OUT}\n")

