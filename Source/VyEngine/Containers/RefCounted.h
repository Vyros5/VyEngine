#pragma once

// EA
#include<EASTL/allocator.h>


namespace VyEngine
{
    struct RefCount
    {
    protected:
        using Allocator = EASTLAllocatorType;

        RefCount() = default;
    
    public:
        ~RefCount()
        {
            // Set reference counts below zero to fire asserts if this object is still accessed.
            refs     = -1;
            weakRefs = -1;
        }

        /// @brief Allocate RefCount using it's default allocator.
        /// @return RefCount*
        static RefCount* Allocate();

        /// @brief Free RefCount using it's default allocator.
        /// @param instance 
        static void Free(RefCount* instance);

        /// @brief Reference count. If below zero, the object has been destroyed.
        int refs     = 0;

        /// @brief Weak reference count.
        int weakRefs = 0;
    };


    /// @brief Base class for intrusively reference-counted objects. These are non-copyable and non-assignable.
    class RefCounted
    {
    public:
        /// @brief Construct. Allocate the reference count structure and set an initial self weak reference.
        RefCounted();

        /// @brief Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
        virtual ~RefCounted();

        /// @brief Prevent copy construction.
        RefCounted(const RefCounted& rhs) = delete;
        
        /// @brief Prevent assignment.
        RefCounted& operator =(const RefCounted& rhs) = delete;


        /// @brief Increment reference count. 
        /// @note Can also be called outside of a SharedPtr for traditional reference counting.
        /// @note Returns new reference count value. Operation is atomic.
        int AddRef();

        /// @brief Decrement reference count and delete self if no more references. 
        /// @note Can also be called outside of a SharedPtr for traditional reference counting.
        /// @note Returns new reference count value. Operation is atomic.
        int ReleaseRef();

        /// @brief Return reference count.
        int Refs() const;

        /// @brief Return weak reference count.
        int WeakRefs() const;

        /// Return pointer to the reference count structure.
        RefCount* RefCountPtr() const { return refCount; }

    private:
        /// @brief Pointer to the reference count struct.
        RefCount* refCount{};
    };
}