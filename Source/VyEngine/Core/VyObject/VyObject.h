#pragma once

#include "Core/Base.h"
#include "Core/RefCounted.h"

namespace VyEngine
{
    class VyObject : public RefCounted
    {
        friend class Context;

    public:
        
        /// @brief Explicit Constructor of a VyObject that takes a Context.
        /// @param context 
        explicit VyObject(Context* context);

        /// @brief Destructor.
        ~VyObject() override;


        Context* GetContext() const { return m_Context; }

    protected:
        Context* m_Context;
        // WeakRef<Context> m_Context;
    };
}