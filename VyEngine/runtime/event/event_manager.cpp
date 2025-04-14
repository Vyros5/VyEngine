#include "event_manager.hpp"
#include "vy_macro.hpp"

namespace VyEngine
{
    EventManager gEventManager;


    void EventManager::Shutdown()
    {
        mEventQueue.clear();
        mSubscribers.clear();
        mSubscribersByEventID.clear();
    }
    

    void EventManager::Subscribe(EventType eventType, UniquePtr<IEventHandlerWrapper>&& handler, EventID eventId)
    {
        if (eventId) 
        {
            auto subscribers = mSubscribersByEventID.find(eventType);
    
            if (subscribers != mSubscribersByEventID.end()) 
            {
                auto& handlersMap = subscribers->second;
                auto handlers = handlersMap.find(eventId);

                if (handlers != handlersMap.end()) 
                {
                    handlers->second.emplace_back(std::move(handler));
                    return;
                }
            }

            mSubscribersByEventID[eventType][eventId].emplace_back(std::move(handler));
        } 
        else 
        {
            auto subscribers = mSubscribers.find(eventType);

            if (subscribers != mSubscribers.end()) 
            {
                auto& handlers = subscribers->second;

                for (auto& it : handlers) 
                {
                    if (it->GetType() == handler->GetType()) 
                    {
                        VY_ASSERT(false, "Attempting to double-register callback");
                        return;
                    }
                }
                handlers.emplace_back(std::move(handler));
            } 
            else 
            {
                mSubscribers[eventType].emplace_back(std::move(handler));
            }
        }
    }
    

    void EventManager::Unsubscribe(EventType eventType, const std::string& handlerName, EventID eventId)
    {
        if (eventId) 
        {
            auto subscribers = mSubscribersByEventID.find(eventType);
            if (subscribers != mSubscribersByEventID.end()) 
            {
                auto& handlersMap = subscribers->second;
                auto handlers = handlersMap.find(eventId);

                if (handlers != handlersMap.end()) 
                {
                    auto& callbacks = handlers->second;

                    for (auto it = callbacks.begin(); it != callbacks.end(); ++it) 
                    {
                        if (it->get()->GetType() == handlerName) 
                        {
                            it = callbacks.erase(it);
                            return;
                        }
                    }
                }
            }
        } 
        else 
        {
            auto handlersIt = mSubscribers.find(eventType);

            if (handlersIt != mSubscribers.end()) 
            {
                auto& handlers = handlersIt->second;

                for (auto it = handlers.begin(); it != handlers.end(); ++it)
                {
                    if (it->get()->GetType() == handlerName) 
                    {
                        it = handlers.erase(it);
                        return;
                    }
                }
            }
        }
    }
    

    void EventManager::Trigger(const Event& event_, EventID eventId)
    {
        for (auto& handler : mSubscribers[event_.GetEventType()]) 
        {
            handler->Execute(event_);
        }
    
        auto& handlersMap = mSubscribersByEventID[event_.GetEventType()];
        auto handlers = handlersMap.find(eventId);

        if (handlers != handlersMap.end())
        {
            auto& callbacks = handlers->second;

            for (auto it = callbacks.begin(); it != callbacks.end();)
            {
                auto& handler = *it;
                handler->Execute(event_);
                
                if (handler->IsDestroyOnSuccess()) 
                {
                    it = callbacks.erase(it);
                } else 
                {
                    ++it;
                }
            }
        }
    }
    

    void EventManager::Queue(UniquePtr<Event>&& event_, EventID eventId)
    {
        mEventQueue.emplace_back(std::move(event_), eventId);
    }
    

    void EventManager::Dispatch()
    {
        for (auto eventIt = mEventQueue.begin(); eventIt != mEventQueue.end();) 
        {
            if (!eventIt->first.get()->isHandled) 
            {
                Trigger(*eventIt->first.get(), eventIt->second);
                eventIt = mEventQueue.erase(eventIt);
            } else 
            {
                ++eventIt;
            }
        }
    }
}