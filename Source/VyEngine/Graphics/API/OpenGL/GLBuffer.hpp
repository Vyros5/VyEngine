#pragma once

#include "Graphics/API/Common/TBuffer.h"
#include "Support/Assert.h"

namespace VyEngine::GFX::API
{
    struct GLBufferContext
    {
        uint32_t ID             = 0;
        uint64_t allocatedBytes = 0;
        Data::EBufferType type  = Data::EBufferType::UNKNOWN;
    };

    using GLBuffer = TBuffer<GLBufferContext>;
}



// namespace VyEngine::GFX::API
// {
//     /**
//      *  Represents a range of memory in a buffer.
//      */
//     struct BufferMemoryRange
//     {
//         uint64_t offset;
//         uint64_t size;
//     };

//     /**
//      *  Represents a buffer. Used to store data on the GPU.
//      */
//     class GLBuffer
//     {
//     public:

//         GLBuffer(EBufferType type);

//         ~GLBuffer();

//         void Bind(std::optional<uint32_t> index = std::nullopt) const;
//         void Unbind() const;

//         /// @brief Allocate memory for the buffer.
//         /// @param size 
//         /// @param usage 
//         /// @return The Size of allocated memory in bytes.
//         uint64_t Allocate(uint64_t size, EAccessSpecifier usage = EAccessSpecifier::STATIC_DRAW);
    
//         /// @brief Uploads data to the buffer.
//         /// @param data 
//         /// @param range 
//         void Upload(const void* data, std::optional<BufferMemoryRange> range = std::nullopt);
    
//         /// @brief Returns true if the buffer is valid (Properly Allocated).
//         bool IsValid() const;

//         /// @brief Returns true if the buffer is empty.
//         bool IsEmpty() const;

//         /// @brief Returns the size of the allocated buffer in bytes.
//         uint64_t GetSize() const;

//         /// @brief Returns the ID of the buffer.
//         uint32_t GetID() const;

//     private:
//         uint32_t m_ID             { 0 };
//         uint64_t m_AllocatedBytes { 0 };
//         EBufferType m_Type        { EBufferType::UNKNOWN };
//     };
// }