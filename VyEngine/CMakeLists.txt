# VyEngine\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html


# Appliation
add_executable(${CMAKE_PROJECT_NAME} ${VY_RUNTIME_DIR}/core/main.cpp)
message(STATUS "[${CMAKE_PROJECT_NAME}]")

# Properties
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
)

# Import Third-Party Libraries
add_subdirectory(libraries)

# SOURCES ======================================================
set(VY_SOURCES

    # Core
    runtime/core/vy_glfw.cpp
    runtime/core/main.cpp
    runtime/core/window.cpp

    # Camera
    runtime/camera/camera.cpp
    runtime/camera/camera_base.cpp
    runtime/camera/camera_controller.cpp
    runtime/camera/perspec_camera.cpp

    # Event
    runtime/event/event_manager.cpp

    # Input
    runtime/input/input.cpp

    # GUI
    runtime/gui/vy_gui.cpp

    # Render
    runtime/render/mesh.cpp
    runtime/render/model.cpp
    runtime/render/shader.cpp
    runtime/render/texture.cpp
    runtime/render/shader_program.cpp

    # VyLib
    runtime/VyLib/vy_file.cpp
    runtime/VyLib/vy_logger.cpp
    runtime/VyLib/vy_platform.cpp
)

# HEADERS ======================================================
set(VY_CORE_HEADERS

    # Core
    runtime/core/vy_glfw.hpp
    runtime/core/window.hpp

    # Camera
    runtime/camera/camera.hpp
    runtime/camera/camera_base.hpp
    runtime/camera/camera_controller.hpp
    runtime/camera/perspec_camera.hpp

    # Event
    runtime/event/event_manager.hpp
    runtime/event/event_handler.hpp
    runtime/event/event.hpp

    # Events
    runtime/event/events/app_event.hpp
    runtime/event/events/key_event.hpp

    # Input
    runtime/input/input.hpp

    # GUI
    runtime/gui/vy_gui.hpp

    # Render
    runtime/render/mesh.hpp
    runtime/render/model.hpp
    runtime/render/shader.hpp
    runtime/render/texture.hpp
    runtime/render/shader_program.hpp

    # VyLib
    runtime/VyLib/vy_file.hpp
    runtime/VyLib/vy_crc32.hpp
    runtime/VyLib/vy_core.hpp
    runtime/VyLib/vy_logger.hpp
    runtime/VyLib/vy_platform.hpp
    runtime/VyLib/vy_log_data.hpp
    runtime/VyLib/vy_log_settings.hpp

    # Memory
    runtime/memory/vertex_memory.hpp
)

# THIRD-PARTY ==================================================
set(THIRD_PARTY_INCLUDE_DIRS
    ${assimp_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
    ${imgui_SOURCE_DIR}/backends
    ${glad_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
    ${fmt_SOURCE_DIR}/include
    ${imgui_SOURCE_DIR}
    ${glm_SOURCE_DIR}
    ${stb_SOURCE_DIR}
)

set(THIRD_PARTY_LIBS
    glfw
    glad
    spdlog
    fmt
    imgui
    assimp
)

# ==============================================================

# Source file paths should be converted to absolute paths.
cmake_policy(SET CMP0076 NEW)

# Add sources to target.
target_sources(${CMAKE_PROJECT_NAME}  
    PRIVATE 
        ${VY_SOURCES}
        ${VY_HEADERS}
)

# Add Include-Libraries to target.
target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime
        ${THIRD_PARTY_INCLUDE_DIRS}
)

# Link Libaries to project.
target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE 
        ${THIRD_PARTY_LIBS}
)

message(STATUS "\n[${CMAKE_PROJECT_NAME}: Linked Libraries]\n")