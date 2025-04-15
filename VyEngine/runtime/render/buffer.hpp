#pragma once

#include "VyLib/vy_core.hpp"
#include <cstdint>
#include <vector>

namespace VyEngine
{
    enum class BuffAttribType
    {
        Null,
        Float1,
        Float2,
        Float3,
        Float4,
        Int1,
        Int2,
        Int3,
        Int4,
        Bool
    };


    static std::uint32_t BuffAttribTypeSize(BuffAttribType type)
    {
        switch (type) 
        {
            case BuffAttribType::Float1: return     sizeof(float);
            case BuffAttribType::Float2: return 2 * sizeof(float);
            case BuffAttribType::Float3: return 3 * sizeof(float);
            case BuffAttribType::Float4: return 4 * sizeof(float);
            case BuffAttribType::Int1:   return     sizeof(int);
            case BuffAttribType::Int2:   return 2 * sizeof(int);
            case BuffAttribType::Int3:   return 3 * sizeof(int);
            case BuffAttribType::Int4:   return 4 * sizeof(int);
            case BuffAttribType::Bool:   return     sizeof(bool);
            case BuffAttribType::Null:   return 0;
        }
        
        return 0;
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////

    struct VertexBufferAttribute
    {
    public:

        size_t mOffset = 0;
        std::uint32_t mSize = 0;
        BuffAttribType mType;
        bool mNormalized = false;

        VertexBufferAttribute() = default;
        VertexBufferAttribute(BuffAttribType type, bool normalized = false) :
            mSize(BuffAttribTypeSize(type)),
            mType(type),
            mNormalized(normalized)
        {}
        
        std::uint32_t GetComponentCount() const
        {
            switch (mType) 
            {
                case BuffAttribType::Float1: return 1;
                case BuffAttribType::Float2: return 2;
                case BuffAttribType::Float3: return 3;
                case BuffAttribType::Float4: return 4;
                case BuffAttribType::Int1:   return 1;
                case BuffAttribType::Int2:   return 2;
                case BuffAttribType::Int3:   return 3;
                case BuffAttribType::Int4:   return 4;
                case BuffAttribType::Bool:   return 1;
                case BuffAttribType::Null:   return 0;
            }

            return 0;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferAttribute> mAttributes;
        std::uint32_t mStride = 0;

    public:
        VertexBufferLayout() = default;
        VertexBufferLayout(const std::initializer_list<VertexBufferAttribute>& attributes) :
            mAttributes(attributes)
        {
            size_t offset = 0;
            for (auto& attrib : mAttributes)
            {
                attrib.mOffset = offset;
                offset  += attrib.mSize;
                mStride += attrib.mSize;
            }
        }

        std::uint32_t GetStride() const { return mStride; }
        const std::vector<VertexBufferAttribute>& GetAttributes() const { return mAttributes; }
    
        std::vector<VertexBufferAttribute>::iterator begin() { return mAttributes.begin(); }
        std::vector<VertexBufferAttribute>::iterator end() { return mAttributes.end(); }
        std::vector<VertexBufferAttribute>::const_iterator begin() const { return mAttributes.begin(); }
        std::vector<VertexBufferAttribute>::const_iterator end() const { return mAttributes.end(); }
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void SetData(const void* data, std::uint32_t size) = 0;
        virtual void SetLayout(const VertexBufferLayout& layout) = 0;

        virtual const std::uint32_t GetID() const = 0;
        virtual const VertexBufferLayout GetLayout() const = 0;

        static SharedPtr<VertexBuffer> Create(std::uint32_t size);
        static SharedPtr<VertexBuffer> Create(float* vertices, std::uint32_t size);
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual const std::uint32_t GetID() const = 0;
        virtual std::uint32_t GetCount() const = 0;

        static SharedPtr<IndexBuffer> Create(std::uint32_t* indices, std::uint32_t count);
    };
}