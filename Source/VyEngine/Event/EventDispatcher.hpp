#pragma once

#include "Event/Event.hpp"

namespace VyEngine
{
    class EventDispatcher
    {
    public:
        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
        using EventFn = std::function<bool(T&)>;

        template<typename T, typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
        using ForwardEventFn = std::function<void(T&)>;

    public:
        EventDispatcher(Event& event) : m_Event(event) {}

        template<typename F>
        bool Dispatch(const EventFn<F>& func)
        {
            if (m_Event.GetType() == F::GetStaticType())
            {
                m_Event.SetHandled(func(dynamic_cast<F&>(m_Event)));
                VY_CORE_INFO("[Dispatcher] Event Handled: {0}", m_Event.ToString());
                return true;
            }

            return false;
        }

        template<typename F>
        void ForwardTo(const ForwardEventFn<F>& func)
        {
            if (m_Event.GetType() == F::GetStaticType())
            {
                func(dynamic_cast<F&>(m_Event));
            }
        }

    private:
        Event& m_Event;
    };
}