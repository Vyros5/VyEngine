# libraries\CMakeLists.txt

include(FetchContent)

# Dependency Linkage
#===========================================================================================

set(GLFW_TAG    3.3.8)
set(IMGUI_TAG   docking)
set(GLM_TAG     2d4c4b4dd31fde06cfffad7915c2b3006402322f)
set(ASSIMP_TAG  0ae66d27039481dc2a507bbc8482f691037c1a5a)
set(STB_TAG     f0569113c93ad095470c54bf34a17b36646bbbb5)

message(STATUS "\nFetching dependencies...\n")

#===========================================================================================

# OpenGL
cmake_policy(SET CMP0079 NEW)
find_package(OpenGL REQUIRED)

if (OpenGL_FOUND)
    message(STATUS "\n[OpenGL]: Libraries - ${OPENGL_LIBRARIES}\n")
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system.\n")
endif()

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

# IMGUI
# FetchContent_Declare(
#     imgui
#     GIT_REPOSITORY  https://github.com/ocornut/imgui.git
#     GIT_TAG         ${IMGUI_TAG}
# )

#===========================================================================================

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm
    GIT_TAG         ${GLM_TAG}
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

FetchContent_MakeAvailable(glfw glm assimp)

message(STATUS "\n[MakeAvailable]")

#===========================================================================================