# GLM

macro(LinkGLM TARGET ACCESS)

set(GLM_VERSION 1.0.1)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm
        GIT_TAG         2d4c4b4dd31fde06cfffad7915c2b3006402322f
    )

    FetchContent_MakeAvailable(glm)
    
    message(STATUS "")
    message(STATUS "=======[GLM ${GLM_VERSION}]=======")
    message(STATUS "")


    target_include_directories(${TARGET} ${ACCESS} ${glm_SOURCE_DIR})

endmacro()