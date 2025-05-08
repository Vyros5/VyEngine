#include "ECS/Entity.h"


namespace VyEngine::ECS
{


    Entity::Entity(u64 entityID, const VyString& name, const VyString& tag, bool &playing) :
        m_EntityID(entityID),
        m_Name(name),
        m_Tag(tag),
        m_Playing(playing)
    {

    }

    Entity::~Entity()
    {
        if (!m_Sleeping)
        {
            if (IsActive()) { OnDisable(); }
            if (m_Awoken && m_Started) { OnDestroy(); }
        }

        
    }

    bool Entity::IsActive() const
    {
        return m_Active && (m_Parent ? m_Parent->IsActive() : true);
    }
        
    bool Entity::IsSelfActive() const
    {
        return m_Active;
    }

    void Entity::SetActive(bool active)
    {
        if (active != m_Active)
        {
            //
            m_Active = active;
            //
        }
    }

    void Entity::SetID(i64 id)
    {
        m_EntityID = id;
    }

    i64 Entity::GetID() const
    {
        return m_EntityID;
    }

    const VyString& Entity::GetName() const
    {
        return m_Name;
    }

    const VyString& Entity::GetTag() const
    {
        return m_Tag;
    }

    void Entity::SetName(const VyString& name)
    {
        m_Name = name;
    }

    void Entity::SetTag(const VyString& tag)
    {
        m_Tag = tag;
    }
}