# ASSIMP - Asset Importer

include(FetchContent)

macro(LinkASSIMP TARGET ACCESS)

    FetchContent_Declare(
        assimp
        GIT_REPOSITORY  https://github.com/assimp/assimp
        GIT_TAG         master
    )

    set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build ASSIMP tools" FORCE)
    set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build tests" FORCE)
    set(ASSIMP_INSTALL              OFF CACHE BOOL "Configure an install for ASSIMP" FORCE)

    message(STATUS "Fetching ASSIMP...")
    FetchContent_MakeAvailable(assimp)

    target_include_directories(${TARGET} ${ACCESS} ${assimp_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} ${ACCESS} assimp)

    add_dependencies(${TARGET} assimp)
    
endmacro()