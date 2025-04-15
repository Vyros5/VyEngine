#include "vertex_array.hpp"
#include "buffer.hpp"
#include "gl_vertex_array.hpp"

namespace VyEngine
{
    SharedPtr<VertexArray> VertexArray::Create()
    {
        MakeUniquePtr<OpenGLVertexArray>();
    }
}
