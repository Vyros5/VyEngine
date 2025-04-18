#include "base_window.hpp"

#include "platform/Windows/gl_window.hpp"

namespace VyEngine
{
    UniquePtr<Window> Window::Create(const WindowProps& props)
    {
        return MakeUniquePtr<OpenGLWindow>(props);
    }
}