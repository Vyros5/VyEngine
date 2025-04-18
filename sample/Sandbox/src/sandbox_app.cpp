#define ENGINE_USE_ENTRYPOINT
#include <VyEngine.hpp>//#include "sandbox_app.hpp"

#include "model_sandbox.hpp"

#include <iostream>
namespace VyEngine
{
    class Sandbox : public Application
    {
    public:
        Sandbox() : Application()
        {
            
        }
    };

    UniquePtr<Application> CreateApplication()
    {
        return std::make_unique<Sandbox>();
    }
}