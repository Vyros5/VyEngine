#include "Core/Context.h"

#include <cassert>

namespace VyEngine
{
    /// @brief Global Context Instance.
    static Context* s_ContextInstance = nullptr;


    Context::Context()
    {
        assert(s_ContextInstance == nullptr);
        s_ContextInstance = this;
    }

    Context::~Context()
    {

    }

    Context* Context::GetInstance()
    {
        return s_ContextInstance;
    }
}