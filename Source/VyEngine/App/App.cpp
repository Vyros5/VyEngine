#include "App/App.h"

#include "Support/Logger/LogDef.h"

namespace VyEngine
{
    VyApplication* VyApplication::s_AppInstance = nullptr;
    

    VyApplication::VyApplication(Context* context)
        : m_Context(context)
    {
        assert(m_Context);

        VYTRACE("Created VyApplication")
    }

    VyApplication::~VyApplication()
    {
        VYTRACE("Destroyed VyApplication")
    }

    bool VyApplication::Isrunning() const
    {
        return !m_Context->window->GetClose();
    }

}