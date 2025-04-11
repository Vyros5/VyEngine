# VyEngine\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html


# Appliation
add_executable(${CMAKE_PROJECT_NAME} ${VY_SOURCE_DIR}/core/main.cpp)
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
    src/core/main.cpp
    src/core/window.cpp
)

set(VY_IO_SOURCES
    src/io/camera.cpp
    src/io/input.cpp
)

set(VY_LIB_SOURCES
    src/VyLib/vy_glfw.cpp
    src/VyLib/vy_file.cpp
    src/VyLib/vy_logger.cpp
)

set(VY_REND_SOURCES
    src/render/mesh.cpp
    src/render/model.cpp
    src/render/shader.cpp
    src/render/texture.cpp
    src/render/shader_program.cpp
)


set(VY_COMPILE_HEADERS
    src/memory/vertex_memory.hpp
)


set(VY_HEADERS
    include/core/window.hpp

    include/io/camera.hpp
    include/io/input.hpp

    include/VyLib/vy_glfw.hpp
    include/VyLib/vy_file.hpp
    include/VyLib/vy_logger.hpp

    include/render/mesh.hpp
    include/render/model.hpp
    include/render/shader.hpp
    include/render/texture.hpp
    include/render/shader_program.hpp
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
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}
        ${glm_SOURCE_DIR}
)


# Link Libaries to project.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    glfw
    glad
    imgui
    assimp
)

get_target_property(OUT ${CMAKE_PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "\n[${CMAKE_PROJECT_NAME} Linked Libraries]: ${OUT}\n")

