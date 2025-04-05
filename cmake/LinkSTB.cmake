# STB

include(FetchContent)

macro(LinkSTB TARGET ACCESS)

    FetchContent_Declare(
        stb
        GIT_REPOSITORY  https://github.com/nothings/stb
        GIT_TAG         f0569113c93ad095470c54bf34a17b36646bbbb5
    )

    message(STATUS "Fetching STB...")
    FetchContent_GetProperties(stb)

    if (NOT stb_POPULATED)

    FetchContent_MakeAvailable(stb)

    endif()

    target_include_directories(${TARGET} ${ACCESS} ${stb_SOURCE_DIR})

endmacro()