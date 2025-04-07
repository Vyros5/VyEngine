# GLAD
# GIT_REPOSITORY  https://github.com/Dav1dde/glad

include(FetchContent)

macro(LinkGLAD TARGET ACCESS)

    set(VY_GLAD_VERSION v2.0.8)

    set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory")
    set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile")
    set(GLAD_API            "" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for")
    set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included")
    set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec")
    set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS")
    set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader")
    set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build")


    FetchContent_Declare(
        glad
        GIT_REPOSITORY      https://github.com/Dav1dde/glad.git
        GIT_TAG             ${VY_GLAD_VERSION}
    )


    FetchContent_MakeAvailable(glad)

    message(STATUS "")
    message(STATUS "=======[GLAD ${VY_GLAD_VERSION}]=======")
    message(STATUS "+ GLAD Source Dir - ${glad_SOURCE_DIR}")
    message(STATUS "+ GLAD Binary Dir - ${glad_BINARY_DIR}")
    message(STATUS "")

    add_library(
            glad
            ${glad_SOURCE_DIR}/src/glad.c
            ${glad_SOURCE_DIR}/include/glad/glad.h
            ${glad_SOURCE_DIR}/include/KHR/khrplatform.h
    )
    target_include_directories(${TARGET} ${ACCESS} ${glad_SOURCE_DIR}/include)
    
    target_link_libraries(${TARGET} ${ACCESS} glad)

endmacro()