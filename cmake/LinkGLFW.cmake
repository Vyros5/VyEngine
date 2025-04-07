# GLFW

include(FetchContent)

macro(LinkGLFW TARGET ACCESS)

    set(GLFW_VERSION 3.3.8)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY  https://github.com/glfw/glfw
        GIT_TAG         ${GLFW_VERSION}
        GIT_PROGRESS    TRUE
        GIT_SHALLOW     TRUE
    )

    FetchContent_MakeAvailable(glfw)
    
    message(STATUS "")
    message(STATUS "=======[GLFW ${GLFW_VERSION}]=======")
    message(STATUS "+ GLFW Source Dir: ${glfw_SOURCE_DIR}")
    message(STATUS "+ GLFW Binary Dir: ${glfw_BINARY_DIR}")
    message(STATUS "")

    target_include_directories(${TARGET} ${ACCESS} ${glfw_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} ${ACCESS} glfw)

endmacro()