#include "vertex_array.hpp"
#include "buffer.hpp"

#include "platform/OpenGL/gl_vertex_array.hpp"

namespace VyEngine
{
    SharedPtr<VertexArray> VertexArray::Create()
    {
        return MakeSharedPtr<OpenGLVertexArray>();
    }
}
