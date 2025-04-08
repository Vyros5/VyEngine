# VyEngine\VyEngine\CMakeLists.txt
# https://cmake.org/cmake/help/latest/command/add_library.html

# add_executable(${CMAKE_PROJECT_NAME} src/core/main.cpp)

add_library(VySources "")

# VyEngine Source Files
set(VY_CORE_SOURCES
    src/core/main.cpp
    src/core/window.cpp
)

# VyEngine Header Files
set(VY_CORE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/core/window.hpp
)

# IO Source Files
set(VY_IO_SOURCES
    src/io/camera.cpp
    src/io/input.cpp
)

# IO Headers Files
set(VY_IO_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/io/camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/io/input.hpp
)

cmake_policy(SET CMP0076 NEW)

target_sources(VySources 
    PRIVATE 
        ${VY_CORE_SOURCES}
        ${VY_IO_SOURCES}
    PUBLIC
        ${VY_CORE_HEADERS}
        ${VY_IO_HEADERS}
)

target_include_directories(VySources PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/include/core
    ${CMAKE_CURRENT_LIST_DIR}/include/io
)