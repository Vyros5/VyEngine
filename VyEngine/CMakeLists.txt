# VyEngine\CMakeLists.txt

# https://cmake.org/cmake/help/latest/command/add_library.html

# HEADERS ======================================================
set(VY_HEADERS

    # Includes
    src/VyEngine.hpp

    # Core
    src/core/application.hpp
    src/core/vy_glfw.hpp
    src/core/window.hpp
    src/core/entry_point.hpp
    src/core/timer.hpp
    src/core/settings_config.hpp

    # Camera
    src/camera/camera.hpp
    src/camera/camera_base.hpp
    src/camera/camera_controller.hpp
    src/camera/perspec_camera.hpp

    # Event
    src/event/event_manager.hpp
    src/event/event_handler.hpp
    src/event/event.hpp

    # Events
    src/event/events/app_event.hpp
    src/event/events/key_event.hpp
    src/event/events/mouse_event.hpp

    # Input
    src/input/input.hpp

    # GUI
    src/gui/vy_gui.hpp

    # Render
    src/render/mesh.hpp
    src/render/model.hpp
    src/render/shader.hpp
    src/render/texture.hpp
    src/render/shader_program.hpp
    src/render/graphics_context.hpp

    src/render/buffer.hpp
    src/render/vertex_array.hpp
    src/render/base_renderer.hpp
    src/render/renderer.hpp

    # Platform
    src/platform/Windows/base_window.hpp
    src/platform/Windows/gl_window.hpp

    src/platform/OpenGL/gl_input.hpp
    src/platform/OpenGL/gl_context.hpp
    src/platform/OpenGL/gl_buffer.hpp
    src/platform/OpenGL/gl_vertex_array.hpp
    src/platform/OpenGL/gl_renderer.hpp

    # VyLib
    src/VyLib/vy_file.hpp
    src/VyLib/vy_crc32.hpp
    src/VyLib/vy_core.hpp
    src/VyLib/vy_logger.hpp

    # Memory
    src/memory/vertex_memory.hpp
)

# SOURCES ======================================================
set(VY_SOURCES

    # Core
    # src/core/main.cpp
    
    src/core/application.cpp
    src/core/vy_glfw.cpp
    src/core/main.cpp
    src/core/window.cpp

    # Camera
    src/camera/camera.cpp
    src/camera/camera_base.cpp
    src/camera/camera_controller.cpp
    src/camera/perspec_camera.cpp

    # Event
    src/event/event_manager.cpp

    # Input
    src/input/input.cpp

    # GUI
    src/gui/vy_gui.cpp

    # Render
    src/render/mesh.cpp
    src/render/model.cpp
    src/render/shader.cpp
    src/render/texture.cpp
    src/render/shader_program.cpp
    
    src/render/buffer.cpp
    src/render/vertex_array.cpp
    src/render/graphics_context.cpp
    src/render/base_renderer.cpp
    src/render/renderer.cpp

    # Platform
    src/platform/Windows/base_window.cpp
    src/platform/Windows/gl_window.cpp

    src/platform/OpenGL/gl_input.cpp
    src/platform/OpenGL/gl_context.cpp
    src/platform/OpenGL/gl_buffer.cpp
    src/platform/OpenGL/gl_vertex_array.cpp
    src/platform/OpenGL/gl_renderer.cpp

    # VyLib
    src/VyLib/vy_file.cpp
    src/VyLib/vy_logger.cpp

    # Headers
    ${VY_HEADERS}
)


set(VENDOR_LIBS
    glfw
    glad
    assimp
    spdlog
    imgui
    fmt
)


#===========================================================================================

# Create Static Library
set(LIBRARY_NAME VyEngineSrc)
add_library(${LIBRARY_NAME} STATIC ${VY_SOURCES})

#===========================================================================================

# Import Third-Party Libraries
add_subdirectory(vendor)

# Path to dependencies
set(LOCAL_VENDOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
message(STATUS "Local Vendor Directory:  " ${LOCAL_VENDOR_PATH})

# Include-Directories
set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
message(STATUS "Engine Source Directory: " ${ENGINE_SOURCE_DIR})


set(ENGINE_INCLUDE_DIRS
    ${glad_SOURCE_DIR}/include   # VyEngine/vendor/glad
    ${glfw_SOURCE_DIR}/include   # out/build/default/_deps/glfw-src/include
    ${assimp_SOURCE_DIR}/include # out\build\default\_deps\assimp-src\include
    ${spdlog_SOURCE_DIR}/include # out\build\default\_deps\spdlog-src\include
    ${imgui_SOURCE_DIR}/backends
    ${glm_SOURCE_DIR}
    
    ${LOCAL_VENDOR_PATH}/stb     # VyEngine\vendor\stb
)

# Add Include-Libraries.
target_include_directories(${LIBRARY_NAME} 
    PUBLIC 
        ${ENGINE_INCLUDE_DIRS}
        ${ENGINE_SOURCE_DIR}
)

# Link Vendor Libraries.
target_link_libraries(${LIBRARY_NAME} PRIVATE ${VENDOR_LIBS})


message(STATUS "[${LIBRARY_NAME}: Linked Libraries]")


# Set configuration properties for VyEngine
if(MSVC)
    message(STATUS "[Compile Options: MSVC]")
    target_compile_options(${LIBRARY_NAME} PUBLIC
        /utf-8
        /W4
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
        /D_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR
        /wd4244 # conversion from 'a' to 'T', possible loss of data
        /wd4267 # conversion from 'size_t' to 'int', possible loss of data
        /wd4245 # conversion from 'int' to 'const size_t', signed/unsigned
                # mismatch
        /wd4100 # unreferenced formal parameter
        /wd4458 # declaration of 'var' hides class member
        /wd4101 # 'var': unreferenced local variable
        /wd4388 # 'token' : signed/unsigned mismatch
        /wd4018 # '>': signed/unsigned mismatch
    )
else()
    message(STATUS "[Compile Options: Other]")
    target_compile_options(${LIBRARY_NAME} PUBLIC 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()
# ==============================================================

# OpenGL
# cmake_policy(SET CMP0079 NEW)
find_package(OpenGL REQUIRED)

if (OpenGL_FOUND)
    message(STATUS "\n[Found OpenGL]\n")
    target_include_directories(${LIBRARY_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${LIBRARY_NAME} PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system.\n")
endif()

# Source file paths should be converted to absolute paths.
# cmake_policy(SET CMP0076 NEW)

# Add sources to target.
# target_sources(${CMAKE_PROJECT_NAME}  
#     PRIVATE 
#         ${VY_SOURCES}
#         ${VY_HEADERS}
# )