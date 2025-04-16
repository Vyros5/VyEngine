#include "graphics_context.hpp"

#include "platform/OpenGL/gl_context.hpp"

namespace VyEngine
{
    UniquePtr<GraphicsContext> GraphicsContext::Create(void* window)
    {
        return MakeUniquePtr<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }
}