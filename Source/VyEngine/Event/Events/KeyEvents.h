#pragma once

#include "Event/Event.hpp"
#include "Window/Data/EInput.h"

using namespace VyEngine::Window::Data;

namespace VyEngine::Events
{
    class KeyEvent : public VyEngine::Event
    {
    public:
        KeyEvent(EKeyCode key) : m_Key(key) {}

        EKeyCode GetKeyCode() const
        {
            return m_Key;
        }

        EVENT_CATEGORY(VY_KEYBOARD_EVENT | VyEngine::EventCategory::VY_INPUT_EVENT)

    protected:
		EKeyCode m_Key;
    };


    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(EKeyCode key, int repeatCount) : KeyEvent(key), m_RepeatCount(repeatCount) {}

        EVENT_TYPE(KeyPressed)

        virtual VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        virtual int GetCategory() const override
        {
            return GetStaticCategory();
        }

        virtual std::string ToString() const override
        {
            return std::string("KeyPressedEvent");
            // return fmt::format("KeyPressedEvent : {0}, repeated count : {1}", m_Key, m_RepeatCount);
        }

    protected:
        int m_RepeatCount{0};
    };


    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(EKeyCode key) : KeyEvent(key) {}

        EVENT_TYPE(KeyReleased)

        virtual VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        virtual int GetCategory() const override
        {
            return GetStaticCategory();
        }

        virtual std::string ToString() const override
        {
            return std::string("KeyReleasedEvent");
            // return fmt::format("KeyReleasedEvent : {0}", m_Key);
        }
    };

	// ============================================================================================

    class KeyTypedEvent : public VyEngine::Event
    {
    public:
        KeyTypedEvent(std::string_view content) : mText(content) {}

        EVENT_TYPE(KeyTyped)
        EVENT_CATEGORY(VY_KEYBOARD_EVENT | VyEngine::EventCategory::VY_INPUT_EVENT)

        virtual VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        virtual int GetCategory() const override
        {
            return GetStaticCategory();
        }

        virtual std::string ToString() const override
        {
            return std::string("KeyTypedEvent");
            // return fmt::format("KeyTypedEvent : {0}", this->mText);
        }

        std::string_view GetText() const
        {
            return mText;
        }

    protected:
        std::string mText;
    };
}