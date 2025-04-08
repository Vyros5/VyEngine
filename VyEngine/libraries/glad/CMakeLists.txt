cmake_minimum_required(VERSION 3.20)
project(glad C)

add_library(glad)
target_sources(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_property(TARGET glad PROPERTY C_STANDARD 99)
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "=======[GLAD]=======\n")