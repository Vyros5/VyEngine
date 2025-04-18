#include "render/base_renderer.hpp"

#include "platform/OpenGL/gl_renderer.hpp"

namespace VyEngine
{
    BaseRenderer::API BaseRenderer::s_API = BaseRenderer::API::OpenGL;

    UniquePtr<BaseRenderer> BaseRenderer::Create()
    {
        return MakeUniquePtr<OpenGLRenderer>();
    }
}