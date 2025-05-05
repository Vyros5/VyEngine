#pragma once

// STD
#include <cstddef>

// EA
#include <EASTL/utility.h>

// VyEngine
#include "Core/Interfaces/INonCopyable.h"

namespace VyEngine
{
    struct AllocatorBlock;
    struct AllocatorNode;

    /// @brief Allocator memory block.
    struct AllocatorBlock
    {
        // Size of a node.
        unsigned nodeSize;

        // Number of nodes in this block.
        unsigned capacity;

        // First free node.
        AllocatorNode* free;

        // Next Allocator Block.
        AllocatorBlock* next;
    };

    /// @brief Allocator Node.
    struct AllocatorNode
    {
        // Next free node.
        AllocatorNode* next;
    };

    /// @brief Initialize a fixed-size allocator with the node size and initial capacity.
    /// @param nodeSize 
    /// @param initCapacity 
    /// @return AllocatorBlock
    AllocatorBlock* AllocatorInit(unsigned nodeSize, unsigned initCapacity = 1);

    /// @brief Uninitialize a fixed-size allocator. Frees all blocks in the chain.
    /// @param allocator 
    void AllocatorUninit(AllocatorBlock* allocator);

    /// @brief Reserve a node. Creates a new block if necessary.
    /// @param allocator 
    /// @return 
    void* AllocatorReserve(AllocatorBlock* allocator);

    /// @brief Free a node. Does not free any blocks.
    /// @param allocator 
    /// @param ptr 
    void AllocatorFree(AllocatorBlock* allocator, void* ptr);

    /// @brief Allocator template class. Allocates objects of a specific class.
    /// @tparam T 
    template<class T>
    class Allocator : private INonCopyable
    {
    public:
        /// @brief Constructor.
        /// @param initCapacity 
        explicit Allocator(unsigned initCapacity = 0) : m_Allocator(nullptr)
        {
            if (initCapacity)
            {
                m_Allocator = AllocatorInit((unsigned)sizeof(T), initCapacity);
            }
        }

        /// @brief Destructor.
        ~Allocator()
        {
            AllocatorUninit(m_Allocator);
        }

        /// @brief Reserve and default-construct an object.
        /// @tparam ...Args 
        /// @param ...args 
        /// @return T*
        template<typename... Args>
        T* Reserve(Args&&... args)
        {
            if (!m_Allocator)
            {
                m_Allocator = AllocatorInit((unsigned)sizeof(T));
            }

            auto* newObject = static_cast<T*>(AllocatorReserve(m_Allocator));
            new(newObject) T(eastl::forward<Args>(args)...);

            return newObject;
        }

        /// @brief Reserve and copy-construct an object.
        T* Reserve(const T& object)
        {
            if (!m_Allocator)
            {
                m_Allocator = AllocatorInit((unsigned)sizeof(T));
            }

            auto* newObject = static_cast<T*>(AllocatorReserve(m_Allocator));
            new(newObject) T(object);

            return newObject;
        }

        /// @brief Destruct and free an object.
        /// @param object 
        void Free(T* object)
        {
            (object)->~T();
            AllocatorFree(m_Allocator, object);
        }

    private:
        AllocatorBlock* m_Allocator;
    };
}