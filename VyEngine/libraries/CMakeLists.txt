# libraries\CMakeLists.txt

include(FetchContent)

# Dependency Linkage
#===========================================================================================

# GLFW
set(GLFW_VERSION 3.3.8)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw
    GIT_TAG         ${GLFW_VERSION}
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
set(GLM_VERSION 2d4c4b4dd31fde06cfffad7915c2b3006402322f)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm
    GIT_TAG         ${GLM_VERSION}
)

FetchContent_MakeAvailable(glm)

message(STATUS "")

#===========================================================================================

# target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
#     ${glad_SOURCE_DIR}/include
#     ${glfw_SOURCE_DIR}/include
#     ${glm_SOURCE_DIR}
# )

# message(STATUS "${glfw_SOURCE_DIR}/include")
# message(STATUS "${glad_SOURCE_DIR}/include")
# message(STATUS "${glm_SOURCE_DIR}\n")

# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
#     glfw
#     glad
# )

#===========================================================================================