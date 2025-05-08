#pragma once

#include "defines.h"

namespace VyEngine::ECS
{
    class Entity;


    class AComponent
    {
    public:
        
        AComponent(Entity& owner);

        virtual ~AComponent();

        virtual void OnAwake() {}

        virtual void OnStart() {}

        virtual void OnEnable() {}

        virtual void OnDisable() {}

        virtual void OnDestroy() {}

        virtual void OnUpdate(f32 dt) {}

        virtual void OnFixedUpdate(f32 dt) {}

        virtual void OnLateUpdate(f32 dt) {}

    public:
        Entity& owner;
    };
}