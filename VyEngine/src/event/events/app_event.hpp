#pragma once

#include "event/event.hpp"

namespace VyEngine::Events
{
    class WindowResizeEvent : public Event
    {
    public:

        EVENT_TYPE("WindowResizeEvent")

        WindowResizeEvent(unsigned int width_, unsigned int height_) : 
            width(width_), 
            height(height_) {}

        std::string ToString() const override
        {
            return "WindowResizeEvent: ";
        }

        unsigned int width { 0 };
        unsigned int height { 0 };
    };


    class WindowCloseEvent : public Event 
    {
    public:

        EVENT_TYPE("WindowCloseEvent")
    };
}