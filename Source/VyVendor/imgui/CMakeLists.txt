cmake_minimum_required(VERSION 3.25)
project(imgui)

add_library(imgui STATIC)

set(IMGUI_SOURCES
    src/imgui.cpp
    src/imgui_demo.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp

    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
)

target_sources(imgui PRIVATE ${IMGUI_SOURCES})

set(IMGUI_INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(imgui PUBLIC ${IMGUI_INC_DIRS})

# GLFW
target_link_libraries(imgui PUBLIC glfw)