#pragma once

#include "event.hpp"

#include <functional>

namespace VyEngine
{
    template<typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;


    class IEventHandlerWrapper
    {
    public:
        virtual ~IEventHandlerWrapper() = default;

        void Execute(const Event& e)
        {
            Call(e);
        }

        virtual std::string GetType() const = 0;
        virtual bool IsDestroyOnSuccess() const = 0;

    private:

        virtual void Call(const Event& e) = 0;
    };


    template<typename EventType>
    class EventHandlerWrapper : public IEventHandlerWrapper
    {
    public:
        
        explicit EventHandlerWrapper(const EventHandler<EventType>& handler, const bool destroyOnSuccess = false) :
                mHandler(handler),
                mHandlerType(mHandler.target_type().name()),
                mDestroyOnSuccess(destroyOnSuccess)
            { }

    private:

        void Call(const Event& e) override
        {
            if (e.GetEventType() == EventType::GetStaticEventType())
            {
                mHandler(static_cast<const EventType&>(e));
            }
        }

        std::string GetType() const override { return mHandlerType; }
        bool IsDestroyOnSuccess() const { return mDestroyOnSuccess; }

        EventHandler<EventType> mHandler;
        const std::string mHandlerType;
        bool mDestroyOnSuccess { false };
    };
}