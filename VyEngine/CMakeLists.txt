# VyEngine\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html


# Appliation
add_executable(${CMAKE_PROJECT_NAME} ${VY_RUNTIME_DIR}/core/main.cpp)
message(STATUS "${CMAKE_PROJECT_NAME}")

# Properties
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Import Third-Party Libraries
add_subdirectory(libraries)


# CORE ================================
set(VY_CORE_SOURCES
    runtime/core/main.cpp
    runtime/core/window.cpp
)

set(VY_CORE_HEADERS
    runtime/core/window.hpp
)

# INPUT ===============================
set(VY_INPUT_SOURCES
    runtime/input/camera.cpp
    runtime/input/input.cpp
)

set(VY_INPUT_HEADERS
    runtime/input/camera.hpp
    runtime/input/input.hpp
)

# GUI =================================
set(VY_GUI_SOURCES
    runtime/gui/vy_gui.cpp
)

set(VY_GUI_HEADERS
    runtime/gui/vy_gui.hpp
)

# VYLIB ===============================
set(VY_LIB_SOURCES
    runtime/VyLib/vy_glfw.cpp
    runtime/VyLib/vy_file.cpp
    runtime/VyLib/vy_logger.cpp
)

set(VY_LIB_HEADERS
    runtime/VyLib/vy_glfw.hpp
    runtime/VyLib/vy_file.hpp
    runtime/VyLib/vy_logger.hpp
)

# RENDER ==============================
set(VY_REND_SOURCES
    runtime/render/mesh.cpp
    runtime/render/model.cpp
    runtime/render/shader.cpp
    runtime/render/texture.cpp
    runtime/render/shader_program.cpp
)

set(VY_REND_HEADERS
    runtime/render/mesh.hpp
    runtime/render/model.hpp
    runtime/render/shader.hpp
    runtime/render/texture.hpp
    runtime/render/shader_program.hpp
)

# MEMORY ==============================
set(VY_MEM_HEADERS
    runtime/memory/vertex_memory.hpp
)


# Source file paths should be converted to absolute paths.
cmake_policy(SET CMP0076 NEW)

# Add sources to target.
target_sources(${CMAKE_PROJECT_NAME}  
    PRIVATE 
        ${VY_CORE_SOURCES}
        ${VY_INPUT_SOURCES}
        ${VY_GUI_SOURCES}
        ${VY_LIB_SOURCES}
        ${VY_REND_SOURCES}

        ${VY_MEMORY_HEADERS}

    PUBLIC
        ${VY_CORE_HEADERS}
        ${VY_INPUT_HEADERS}
        ${VY_GUI_HEADERS}
        ${VY_LIB_HEADERS}
        ${VY_REND_HEADERS}
)

# Add Include-Libraries to target.
target_include_directories(${CMAKE_PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/core
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/gui
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/input
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/memory
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/render
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/VyLib

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
message(STATUS "\n[${CMAKE_PROJECT_NAME}: Linked Libraries]\n")

