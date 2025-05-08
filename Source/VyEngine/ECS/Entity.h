#pragma once

#include "defines.h"

namespace VyEngine::ECS
{
    /**
     *  Main class of the ECS.
     *  Composes of components and behaviors (scripts).
     */
    class Entity
    {
    public:
        
        /// @brief Constructor
        /// @param entityID 
        /// @param name 
        /// @param tag 
        /// @param playing 
        Entity(u64 entityID, const VyString& name, const VyString& tag, bool &playing);
        
        virtual ~Entity();


        bool IsActive() const;
        
        bool IsSelfActive() const;

        void SetActive(bool active);

        void SetID(i64 id);

        i64 GetID() const;

        const VyString& GetName() const;

        const VyString& GetTag() const;

        void SetName(const VyString& name);

        void SetTag(const VyString& tag);


        void OnAwake();

        void OnStart();

        void OnEnable();

        void OnDisable();

        void OnDestroy();

        void OnUpdate(f32 dt);

        void OnFixedUpdate(f32 dt);

        void OnLateUpdate(f32 dt);

    
    private:
        Entity(const Entity& other) = delete;
    
        /* Settings */
        VyString m_Name;
        VyString m_Tag;
        bool     m_Active = true;
        bool&    m_Playing;

        /* Internal Settings */
        i64 m_EntityID;
        bool m_Started   { false };
        bool m_Awoken    { false };
        bool m_Sleeping  { true  };
        bool m_WasActive { false };
        bool m_Destroyed { false };

        /* Parenting */
        i64 m_ParentID   = 0;
        Entity* m_Parent = nullptr;
        std::vector<Entity*> m_Children;

        /* Entity Components */

    };
}