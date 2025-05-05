#include "Containers/RefCounted.h"

// EA
#include <EASTL/internal/thread_support.h>

// STD
#include <cassert>

namespace VyEngine
{
    RefCount* RefCount::Allocate()
    {
        void* const memory = EASTLAlloc(*eastl::get_default_allocator((Allocator*)nullptr), sizeof(RefCount));
        assert(memory != nullptr);
        return ::new(memory) RefCount();
    }

    void RefCount::Free(RefCount* instance)
    {
        instance->~RefCount();
        EASTLFree(*eastl::get_default_allocator((Allocator*)nullptr), instance, sizeof(RefCount));
    }

    // ============================================================================================

    RefCounted::RefCounted() : refCount(RefCount::Allocate())
    {
        // Hold a weak ref to self to avoid possible double delete of the refcount.
        refCount->weakRefs++;
    }

    RefCounted::~RefCounted()
    {
        assert(refCount);
        assert(refCount->refs == 0);
        assert(refCount->weakRefs > 0);

        // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist.
        refCount->refs = -1;

        if (eastl::Internal::atomic_decrement(&refCount->weakRefs) == 0)
        {
            RefCount::Free(refCount);
        }

        refCount = nullptr;
    }


    int RefCounted::AddRef()
    {
        int references = eastl::Internal::atomic_increment(&refCount->refs);
        assert(references > 0);
        
        return references;
    }


    int RefCounted::ReleaseRef()
    {
        int references = eastl::Internal::atomic_decrement(&refCount->refs);
        assert(references >= 0);

        if (references == 0)
        {
            delete this;
        }

        return references;
    }


    int RefCounted::Refs() const
    {
        return refCount->refs;
    }


    int RefCounted::WeakRefs() const
    {
        // Subtract one to not return the internally held reference
        return refCount->weakRefs - 1;
    }
}