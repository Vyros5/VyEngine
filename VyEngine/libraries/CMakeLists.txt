# libraries\CMakeLists.txt

include(FetchContent)

# Dependency Linkage
#===========================================================================================

# GLFW
set(GLFW_TAG 3.3.8)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw
    GIT_TAG         ${GLFW_TAG}
    GIT_PROGRESS    TRUE
    GIT_SHALLOW     TRUE
)

message(STATUS "\n=======[GLFW ${GLFW_VERSION}]=======")
message(STATUS "+ GLFW Source Dir: ${glfw_SOURCE_DIR}")
message(STATUS "+ GLFW Binary Dir: ${glfw_BINARY_DIR}\n")

FetchContent_MakeAvailable(glfw)

#===========================================================================================

# GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

#===========================================================================================

cmake_policy(SET CMP0079 NEW)

# OpenGL
find_package(OpenGL REQUIRED)

if (OpenGL_FOUND)
    message(STATUS "[OpenGL]: Libararies - ${OPENGL_LIBRARIES}\n")
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system.\n")
endif()

#===========================================================================================

# GLM
set(GLM_TAG 2d4c4b4dd31fde06cfffad7915c2b3006402322f)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm
    GIT_TAG         ${GLM_TAG}
)

FetchContent_MakeAvailable(glm)

#===========================================================================================

# ASSIMP
set(ASSIMP_TAG 0ae66d27039481dc2a507bbc8482f691037c1a5a)

message(STATUS "\n=======[ASSIMP]=======\n")

FetchContent_Declare(
    assimp
    GIT_REPOSITORY  https://github.com/assimp/assimp.git
    GIT_TAG         ${ASSIMP_TAG}
)

set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build ASSIMP tools" FORCE)
set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build tests" FORCE)
set(ASSIMP_INSTALL              OFF CACHE BOOL "Configure an install for ASSIMP" FORCE)

FetchContent_MakeAvailable(assimp)

#===========================================================================================

# STB
message(STATUS "\n=======[STB]=======\n")
FetchContent_Declare(
    stb
    GIT_REPOSITORY  https://github.com/nothings/stb.git
    GIT_TAG         master
)

FetchContent_MakeAvailable(stb)

#===========================================================================================