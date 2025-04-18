#pragma once

#include <VyEngine.hpp>

class Sandbox : public VyEngine::Application
{
public: 
    Sandbox();

    virtual void OnCreate();
    virtual void OnUpdate(float dt);
    virtual void OnRender(float dt);
    virtual void OnDestroy();
};