#pragma once

#include <vector>
#include <unordered_map>

#include "event_handler.hpp"

namespace VyEngine::Events
{
    using EventType = uint32_t;
    using EventID   = uint64_t;


    class EventManager
    {
    public:

        EventManager() = default;
        EventManager(const EventManager&) = delete;
        const EventManager& operator=(const EventManager&) = delete;

        void Subscribe(EventType eventType, UniquePtr<IEventHandlerWrapper>&& handler, EventID eventId);
        void Unsubscribe(EventType eventType, const std::string& handlerName, EventID eventId);
        void Trigger(const Event& event_, EventID eventId);
        void Queue(UniquePtr<Event>&& event_, EventID eventId);
        void Dispatch();
        void Shutdown();

    private:

        std::vector<std::pair<UniquePtr<Event>, EventID>> mEventQueue;
        std::unordered_map<EventType, std::vector<UniquePtr<IEventHandlerWrapper>>> mSubscribers;
        std::unordered_map<EventType, std::unordered_map<EventID, std::vector<UniquePtr<IEventHandlerWrapper>>>> mSubscribersByEventID;
    };


    extern EventManager gEventManager;

    template<typename EventType>
    inline void Subscribe(const EventHandler<EventType>& callback, EventID eventId = 0, const bool unsubscribeOnSuccess = false)
    {
        UniquePtr<IEventHandlerWrapper> handler = MakeUniquePtr<EventHandlerWrapper<EventType>>(callback, unsubscribeOnSuccess);
        gEventManager.Subscribe(EventType::GetStaticEventType(), std::move(handler), eventId);
    }

    template<typename EventType>
    inline void Unsubscribe(const EventHandler<EventType>& callback, EventID eventId = 0)
    {
        const std::string handlerName = callback.target_type().name();
        gEventManager.Unsubscribe(EventType::GetStaticEventType(), handlerName, eventId);
    }
    
    inline void Trigger(const Event& triggeredEvent, EventID eventId = 0)
    {
        gEventManager.Trigger(triggeredEvent, eventId);
    }
    
    inline void Queue(UniquePtr<Event>&& queuedEvent, EventID eventId = 0)
    {
        gEventManager.Queue(std::forward<UniquePtr<Event>>(queuedEvent), eventId);
    }
}