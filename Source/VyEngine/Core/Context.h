#pragma once

#include <EASTL/unique_ptr.h>

#include "Containers/Pointers.h"

#include "Core/Base.h"

namespace VyEngine
{
    class Context : public RefCounted
    {
        friend class Object;

    public:
        
        Context();

        ~Context() override;
    
        /// @brief Return global instance of Context Object.
        /// @note Only one Context may exist within the application.
        /// @return Context
        static Context* GetInstance();


        // Object* GetSubSystem() const;


    };
}