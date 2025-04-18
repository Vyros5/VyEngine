# VyEngine\vendor\CMakeLists.txt

include(FetchContent)

# Dependency Linkage
#===========================================================================================

set(GLFW_TAG    3.3.8)
set(GLM_TAG     2d4c4b4dd31fde06cfffad7915c2b3006402322f)
set(FMT_TAG     e814b5fabf2cbd61aeca6fdb99e99961f23fcdb7)
set(SPDLOG_TAG  bb8694b50f186cb005d32cec76fe94ae25998c0d)
set(ASSIMP_TAG  0ae66d27039481dc2a507bbc8482f691037c1a5a)

message(STATUS "\nFetching dependencies...\n")

#===========================================================================================



#===========================================================================================

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw
    GIT_TAG         ${GLFW_TAG}
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)

#===========================================================================================

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm
    GIT_TAG         ${GLM_TAG}
)

#===========================================================================================

# option(SPDLOG_FMT_EXTERNAL "Use external fmt library instead of bundled" ON)

# FMT
set(SPDLOG_FMT_EXTERNAL ON)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
    GIT_TAG         ${FMT_TAG}
)

#===========================================================================================

# SPDLOG
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         ${SPDLOG_TAG}
)
#===========================================================================================

# ASSIMP
FetchContent_Declare(
    assimp
    GIT_REPOSITORY  https://github.com/assimp/assimp.git
    GIT_TAG         ${ASSIMP_TAG}
)

set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build ASSIMP tools" FORCE)
set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build tests" FORCE)
set(ASSIMP_INSTALL              OFF CACHE BOOL "Configure an install for ASSIMP" FORCE)

#===========================================================================================

# GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

#===========================================================================================

# IMGUI
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

#===========================================================================================

FetchContent_MakeAvailable(glfw glm fmt spdlog assimp)

message(STATUS "\n[MakeAvailable]\n")

#===========================================================================================