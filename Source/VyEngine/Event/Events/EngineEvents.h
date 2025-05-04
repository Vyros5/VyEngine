#pragma once

#include "Event/Event.hpp"

namespace VyEngine::Events
{
    class EngineClosedEvent : public VyEngine::Event
    {
    public:
        EngineClosedEvent(std::string_view reason) : Event(), m_Reason(reason)
        {
            m_Name = "EngineClosed";
        }

        ~EngineClosedEvent() = default;

        void SetReason(std::string_view reason)
        {
            m_Reason = reason;
        }

        VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        int GetCategory() const override
        {
            return GetStaticCategory();
        }

        std::string ToString() const override
        {
            return std::string("EngineClosedEvent");
            // return fmt::format("{}: {}", m_Name, mReason);
        }

        EVENT_TYPE(EngineClosed)
        EVENT_CATEGORY(VY_ENGINE_EVENT)

    private:
        std::string m_Reason{};
    };
}