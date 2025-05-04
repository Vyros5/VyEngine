
set(GLAD_SOURCES
    src/glad.c
    include/glad/glad.h
    include/KHR/khrplatform.h
)

add_library(glad STATIC ${GLAD_SOURCES})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_property(TARGET glad PROPERTY C_STANDARD 99)