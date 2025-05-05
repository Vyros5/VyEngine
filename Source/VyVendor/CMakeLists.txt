# ./Source/VyVendor - Vendor Library

cmake_minimum_required(VERSION 3.20)
project(VyVendor CXX C)

include(FetchContent)

#==================================================================================================
# Package Version Tags

set(GLFW_TAG    e7ea71be039836da3a98cea55ae5569cb5eb885c)
set(GLM_TAG     2d4c4b4dd31fde06cfffad7915c2b3006402322f)
set(EASTL_TAG   7fadbf0da01e6f6e0e7038b1b34343a069b8fc51)
set(FMT_TAG     505ee058f7d5ec2a2a80eae82011ad48122b1551)
set(SPDLOG_TAG  bb8694b50f186cb005d32cec76fe94ae25998c0d)
set(ASSIMP_TAG  ac5988422a7f1898b25c13fb5fb068c646a4c544)

#==================================================================================================

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         ${GLFW_TAG}
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(glfw)

#==================================================================================================

# GLAD
add_subdirectory(glad)

#==================================================================================================

# IMGUI
add_subdirectory(imgui)

#===========================================================================================

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         ${GLM_TAG}
)

FetchContent_MakeAvailable(glm)

#==================================================================================================

# EASTL
add_subdirectory(EASTL)

#==================================================================================================

# SPDLOG
option(SPDLOG_FMT_EXTERNAL "Use external fmt library instead of bundled" OFF)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         ${SPDLOG_TAG}
)

FetchContent_MakeAvailable(spdlog)

#==================================================================================================

# ASSIMP
FetchContent_Declare(
    assimp
    GIT_REPOSITORY  https://github.com/assimp/assimp.git
    GIT_TAG         ${ASSIMP_TAG}
    GIT_PROGRESS    FALSE
)

set(ASSIMP_SHARED_LIBS  OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS  OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL      OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(assimp)

#==================================================================================================
