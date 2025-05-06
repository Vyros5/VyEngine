#pragma once

#include "Core/Base.h"
#include "Core/Context.h"

namespace VyEngine
{
    class Object //: public RefCounted
    {
        // friend class Context;

    public:
        
        /// @brief Explicit Constructor of a Object that takes a Context.
        /// @param context 
        explicit Object(Context* context);

        /// @brief Destructor.
        ~Object();


        Context* GetContext() const { return m_Context; }

    protected:
        // Execution Context
        WeakPtr<Context> m_Context;

    };
}