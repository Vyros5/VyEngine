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


add_subdirectory(libraries)


# VyEngine Source Files
set(VY_SOURCES
    src/main.cpp
    src/window.cpp
    src/vy_glfw.cpp
    src/camera.cpp
    src/input.cpp
)

set(VY_COMPILE_HEADERS
    src/vertex_memory.hpp
)

set(VY_HEADERS
    include/window.hpp
    include/camera.hpp
    include/input.hpp
    include/vy_glfw.hpp
)

cmake_policy(SET CMP0076 NEW)

target_sources(${CMAKE_PROJECT_NAME}  
    PRIVATE 
        ${VY_SOURCES}
        ${VY_COMPILE_HEADERS}
    PUBLIC
        ${VY_HEADERS}
)

target_include_directories(${CMAKE_PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries
    PRIVATE
        ${glad_SOURCE_DIR}/include
        ${glfw_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
)

message(STATUS "${glfw_SOURCE_DIR}/include")
message(STATUS "${glad_SOURCE_DIR}/include")
message(STATUS "${glm_SOURCE_DIR}\n")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    glfw
    glad
)

message(STATUS "[CURRENT INC_DIR]: ${CMAKE_CURRENT_SOURCE_DIR}/include\n")
# target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
#     ${glad_SOURCE_DIR}/include
#     ${glfw_SOURCE_DIR}/include
#     ${glm_SOURCE_DIR}
# )

