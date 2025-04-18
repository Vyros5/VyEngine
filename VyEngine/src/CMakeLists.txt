# VyEngine\src\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html

# HEADERS ======================================================
set(VYENGINE_HEADERS

    # Core
    core/application.hpp
    core/vy_glfw.hpp
    core/window.hpp
    core/scene.hpp
    core/entry_point.hpp
    core/timer.hpp
    core/settings_config.hpp

    # Camera
    camera/camera.hpp
    camera/camera_base.hpp
    camera/camera_controller.hpp
    camera/perspec_camera.hpp

    # Event
    event/event_manager.hpp
    event/event_handler.hpp
    event/event.hpp

    # Events
    event/events/app_event.hpp
    event/events/key_event.hpp
    event/events/mouse_event.hpp

    # Input
    input/input.hpp

    # GUI
    gui/vy_gui.hpp

    # Render
    render/mesh.hpp
    render/model.hpp
    render/shader.hpp
    render/texture.hpp
    render/shader_program.hpp
    render/graphics_context.hpp

    render/buffer.hpp
    render/vertex_array.hpp

    # Platform
    platform/Windows/base_window.hpp
    platform/Windows/gl_window.hpp

    platform/OpenGL/gl_input.hpp
    platform/OpenGL/gl_context.hpp
    platform/OpenGL/gl_buffer.hpp
    platform/OpenGL/gl_vertex_array.hpp

    # VyLib
    VyLib/vy_file.hpp
    VyLib/vy_crc32.hpp
    VyLib/vy_core.hpp
    VyLib/vy_logger.hpp

    # Memory
    memory/vertex_memory.hpp
)

# SOURCES ======================================================
set(VYENGINE_SOURCES

    # Core
    core/main.cpp
    core/application.cpp
    core/vy_glfw.cpp
    core/main.cpp
    core/window.cpp

    # Camera
    camera/camera.cpp
    camera/camera_base.cpp
    camera/camera_controller.cpp
    camera/perspec_camera.cpp

    # Event
    event/event_manager.cpp

    # Input
    input/input.cpp

    # GUI
    gui/vy_gui.cpp

    # Render
    render/mesh.cpp
    render/model.cpp
    render/shader.cpp
    render/texture.cpp
    render/shader_program.cpp
    
    render/buffer.cpp
    render/vertex_array.cpp
    render/graphics_context.cpp

    # Platform
    platform/Windows/base_window.cpp
    platform/Windows/gl_window.cpp

    platform/OpenGL/gl_input.cpp
    platform/OpenGL/gl_context.cpp
    platform/OpenGL/gl_buffer.cpp
    platform/OpenGL/gl_vertex_array.cpp

    # VyLib
    VyLib/vy_file.cpp
    VyLib/vy_logger.cpp

    # Headers
    ${VY_HEADERS}
)