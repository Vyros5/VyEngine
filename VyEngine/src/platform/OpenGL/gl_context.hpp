#pragma once

#include "render/graphics_context.hpp"

struct GLFWwindow;

namespace VyEngine
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* mWindowHandle = nullptr;
    };
}