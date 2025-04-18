#include "platform/OpenGL/gl_renderer.hpp"

#include <glad/glad.h>

namespace VyEngine
{
    void OpenGLRenderer::Init()
    {

    }

    void OpenGLRenderer::SetViewport(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h)
    {
        glViewport(x, y, w, h);
    }

    
    void OpenGLRenderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.b, color.g, color.a);
    }

    void OpenGLRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::ClearColorBit()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void OpenGLRenderer::EnableDepthTesting(bool enabled)
    {
        if (enabled)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL); // <-------------------------------------
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void OpenGLRenderer::EnableDepthMask(bool enabled)
    {
        glDepthMask(enabled ? GL_TRUE : GL_FALSE);
    }

    void OpenGLRenderer::EnableFaceCulling(bool enabled)
    {
        if (enabled)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }

}