# ASSIMP - Asset Importer

include(FetchContent)

macro(LinkASSIMP TARGET ACCESS)

    FetchContent_Declare(
        assimp
        GIT_REPOSITORY  https://github.com/assimp/assimp
        GIT_TAG         master
    )

    message(STATUS "Fetching ASSIMP...")
    FetchContent_GetProperties(assimp)

    if (NOT assimp_POPULATED)

        FetchContent_MakeAvailable(assimp) 
        # FetchContent_Populate(assimp)

        # Just configure ASSIMP only
        set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build ASSIMP tools" FORCE)
        set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build tests" FORCE)
        set(ASSIMP_INSTALL              OFF CACHE BOOL "Configure an install for ASSIMP" FORCE)

        # This excludes ASSIMP from being rebuilt when ALL_BUILD is built
        # it will only be built when a target is built that has a dependency on ASSIMP
        add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR} EXCLUDE_FROM_ALL)

        # Set the target's folders
        set_target_properties(assimp PROPERTIES FOLDER ${PROJECT_NAME}/thirdparty)
        set_target_properties(IrrXML PROPERTIES FOLDER ${PROJECT_NAME}/thirdparty)
        set_target_properties(zlibstatic PROPERTIES FOLDER ${PROJECT_NAME}/thirdparty)

    endif()

    target_include_directories(${TARGET} ${ACCESS} ${assimp_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} ${ACCESS} assimp)

    add_dependencies(${TARGET} assimp)
endmacro()