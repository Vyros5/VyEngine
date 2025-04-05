# GLAD

include(FetchContent)

macro(LinkGLAD TARGET ACCESS)

    FetchContent_Declare(
        glad
        GIT_REPOSITORY  https://github.com/Dav1dde/glad
        GIT_TAG         v2.0.8
        GIT_PROGRESS    TRUE
        GIT_SHALLOW     TRUE
    )

    message(STATUS "[GLAD: Fetching...]")
    FetchContent_MakeAvailable(glad)

    target_include_directories(${TARGET} ${ACCESS} ${glad_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} ${ACCESS} glad)

    # add_dependencies(${TARGET} glad)
    
endmacro()