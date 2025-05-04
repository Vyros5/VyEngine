#include "Core/Context.h"



namespace VyEngine::Core
{
    /// @brief Global Context Instance.
    static Context* s_ContextInstance = nullptr;


    Context::Context()
    {

    }

    Context::~Context()
    {

    }

    Context* Context::GetInstance()
    {
        return s_ContextInstance;
    }
}