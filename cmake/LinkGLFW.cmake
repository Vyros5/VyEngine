# GLFW

include(FetchContent)

macro(LinkGLFW TARGET ACCESS)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw
        GIT_TAG         3.3.8
        GIT_PROGRESS    TRUE
        GIT_SHALLOW     TRUE
    )

    message(STATUS "[GLFW: Fetching...]")
    FetchContent_MakeAvailable(glfw)

    target_include_directories(${TARGET} ${ACCESS} ${glfw_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} ${ACCESS} glfw)

    # add_dependencies(${TARGET} glfw)

endmacro()