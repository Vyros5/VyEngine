#pragma once

#include "Core/Base.h"

namespace VyEngine::Core
{
    class Context
    {
        friend class Object;

    public:
        
        Context();

        ~Context();
    
        /// @brief Return global instance of Context Object.
        /// @note Only one Context may exist within the application.
        /// @return Context
        static Context* GetInstance();


        Object* GetSubSystem() const;


    };
}