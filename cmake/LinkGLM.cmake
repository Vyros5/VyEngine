# GLM

macro(LinkGLM TARGET ACCESS)

set(GLM_VERSION 2d4c4b4dd31fde06cfffad7915c2b3006402322f)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm
        GIT_TAG         ${GLM_VERSION}
    )

    FetchContent_MakeAvailable(glm)
    
    message(STATUS "")

    target_include_directories(${TARGET} ${ACCESS} ${glm_SOURCE_DIR})

endmacro()