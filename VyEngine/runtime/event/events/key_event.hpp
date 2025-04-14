#pragma once

#include "input_codes.hpp"
#include "event.hpp"

namespace VyEngine
{
    class KeyPressedEvent : public Event
    {
    public:

        EVENT_TYPE("KeyPressedEvent")

        KeyPressedEvent(int keyCode, int repeatCount) : key(keyCode), repeatCount(repeatCount) {}

        std::string ToString() const override
        {
            return "KeyPressedEvent: ";
        }

        KeyCode key { 0 };
        int repeatCount { 0 };
    };


    class KeyReleasedEvent : public Event
    {
    public:

        EVENT_TYPE("KeyReleasedEvent")

        KeyReleasedEvent(int keyCode) : key(keyCode) {}

        std::string ToString() const override
        {
            return "KeyReleasedEvent: ";
        }

        KeyCode key { 0 };
    };


    class KeyTypedEvent : public Event
    {
    public:

        EVENT_TYPE("KeyTypedEvent")

        KeyTypedEvent(int keyCode) : key(keyCode) {}

        std::string ToString() const override
        {
            return "KeyTypedEvent: ";
        }

        KeyCode key { 0 };
    };
}