#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace VyEngine::core
{
    GLFWwindow* InitGLFW(int scrWidth, int scrHeight, const char* title);

    void glDebugOutput(GLenum source,
        GLenum type,
        unsigned int id,
        GLenum severity,
        GLsizei length,
        const char *message,
        const void *userParam
    );
}