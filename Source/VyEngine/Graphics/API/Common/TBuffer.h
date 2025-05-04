#pragma once

#include <optional>

#include "Graphics/Data/EBuffer.h"
// #include "Core/Interfaces/IBindable.h"


namespace VyEngine::GFX::API
{
    /**
     *  Represents a range of memory in a buffer.
     */
    struct BufferMemoryRange
    {
        uint64_t offset;
        uint64_t size;
    };

    /**
     *  Represents a buffer. Used to store data on the GPU.
     */
    template<class BufferContext>
    class TBuffer
    {
    public:

        /// @brief Creates a buffer of an EBufferType.
        TBuffer(Data::EBufferType type);

        /// @brief Destroys the buffer.
        ~TBuffer();

        /// @brief Allocates memory for the buffer.
        /// @param size 
        /// @param usage 
        /// @return The Size of allocated memory in bytes.
        uint64_t Allocate(uint64_t size, Data::EAccessSpecifier usage = Data::EAccessSpecifier::STATIC_DRAW);
    
        /// @brief Uploads data to the buffer.
        /// @param data 
        /// @param range 
        void Upload(const void* data, std::optional<BufferMemoryRange> range = std::nullopt);
    
        /// @brief Binds the buffer.
        void Bind(std::optional<uint32_t> index = std::nullopt) const;
        
        /// @brief Unbinds the buffer.
        void Unbind() const;

        /// @brief Returns true if the buffer is valid (Properly Allocated).
        bool IsValid() const;

        /// @brief Returns true if the buffer is empty.
        bool IsEmpty() const;

        /// @brief Returns the size of the allocated buffer in bytes.
        uint64_t GetSize() const;

        /// @brief Returns the ID of the buffer.
        uint32_t GetID() const;

    protected:
        BufferContext m_Buffer;
    };
}