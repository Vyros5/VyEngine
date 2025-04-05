# GLM

macro(LinkGLM TARGET ACCESS)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm
        GIT_TAG         master
    )

    message(STATUS "Fetching GLM...")
    FetchContent_GetProperties(glm)

    if (NOT glm_POPULATED)

        FetchContent_MakeAvailable(glm)

    endif()

    target_include_directories(${TARGET} ${ACCESS} ${glm_SOURCE_DIR})

endmacro()