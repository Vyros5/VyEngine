#include "gl_vertex_array.hpp"

#include <glad/glad.h>

namespace VyEngine
{
    static GLenum BuffAttribToGLenum(BuffAttribType type)
    {
        switch (type) 
        {
            case BuffAttribType::Float1: return GL_FLOAT;
            case BuffAttribType::Float2: return GL_FLOAT;
            case BuffAttribType::Float3: return GL_FLOAT;
            case BuffAttribType::Float4: return GL_FLOAT;
            case BuffAttribType::Int1:   return GL_INT;
            case BuffAttribType::Int2:   return GL_INT;
            case BuffAttribType::Int3:   return GL_INT;
            case BuffAttribType::Int4:   return GL_INT;
            case BuffAttribType::Bool:   return GL_BOOL;
        }

        return 0;
    }

    // ==================================================================================

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &mID);
    }


    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &mID);
    }


    void OpenGLVertexArray::AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer)
    {
        const VertexBufferLayout& layout = vertexBuffer->GetLayout();
        glVertexArrayVertexBuffer(mID, mVertexBufferIndex, vertexBuffer->GetID(), 0, layout.GetStride());

        unsigned int attribIndex = 0;
        for (const auto& attrib : layout.GetAttributes())
        {
            glEnableVertexArrayAttrib(mID, attribIndex);

            glVertexArrayAttribFormat(
                mID, 
                attribIndex, 
                attrib.GetComponentCount(), 
                BuffAttribToGLenum(attrib.mType),
                attrib.mNormalized ? GL_TRUE : GL_FALSE,
                (GLuint)attrib.mOffset
            );

            glVertexArrayAttribBinding(mID, attribIndex, mVertexBufferIndex);
            attribIndex++;
        }

        mVertexBufferIndex++;
        mVertexBuffers.push_back(vertexBuffer);
    }


    void OpenGLVertexArray::SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer)
    {
        glVertexArrayElementBuffer(mID, indexBuffer->GetID());
        mIndexBuffer = indexBuffer;
    }


    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(mID);
    }
}