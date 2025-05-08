#include "ECS/Components/AComponent.h"

#include "ECS/Entity.h"

VyEngine::ECS::AComponent::AComponent(Entity& p_owner) : owner(p_owner) {}

VyEngine::ECS::AComponent::~AComponent()
{
    if (owner.IsActive())
    {
        OnDisable();
        OnDestroy();
    }
}