#pragma once

#include <VyEngine.hpp>

class ModelSandbox : public VyEngine::Application
{
public:
    ModelSandbox();

    void OnUpdate(float dt) override;
    void OnRender(float dt) override;
    void OnProcessInput(float dt) override;
};