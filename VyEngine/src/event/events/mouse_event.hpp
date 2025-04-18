#pragma once 

#include "input/input_codes.hpp"
#include "event/event.hpp"

namespace VyEngine::Events
{
    class MouseMovedEvent : public Event 
    {
    public:

        EVENT_TYPE("MouseMovedEvent")
    
        MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}
    
        std::string ToString() const override
        {
            return "MouseMovedEvent: "; // return fmt::format("MouseMovedEvent: {}, {}", mouseX, mouseY);
        }
    
    public:
        float mouseX { 0.0f };
        float mouseY { 0.0f };
    };
    
    
    class MouseScrolledEvent : public Event 
    {
    public:

        EVENT_TYPE("MouseScrolledEvent")
    
        MouseScrolledEvent(float xOffset_, float yOffset_) : xOffset(xOffset_), yOffset(yOffset_) {}
    
        std::string ToString() const override
        {
            return "MouseScrolledEvent: "; // return fmt::format("MouseScrolledEvent: {}, {}", xOffset, yOffset);
        }
    
    public:
        float xOffset { 0.0f };
        float yOffset { 0.0f };
    };
    
    
    class MouseButtonPressedEvent : public Event 
    {
    public:

        EVENT_TYPE("MouseButtonPressedEvent")
    
        MouseButtonPressedEvent(int button) : button(button) {}
    
        std::string ToString() const override
        {
            return "MouseButtonPressedEvent: "; // return fmt::format("MouseButtonPressedEvent: {}", button);
        }
    
    public:
        MouseCode button { 0 };
    };
    

    class MouseButtonReleasedEvent : public Event 
    {
    public:

        EVENT_TYPE("MouseButtonReleasedEvent")
    
        MouseButtonReleasedEvent(int button) : button(button) {}
    
        std::string ToString() const override
        {
            return "MouseButtonReleasedEvent: "; // return fmt::format("MouseButtonReleasedEvent: {}", button);
        }
    
    public:
        MouseCode button { 0 };
    };
}