cmake_minimum_required(VERSION 3.20)
project(glad C)

add_library(glad)
target_sources(glad PRIVATE src/glad.c)
target_include_directories(glad PUBLIC include)
set_property(TARGET glad PROPERTY C_STANDARD 99)
message(STATUS "[GLAD]")