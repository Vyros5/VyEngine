#pragma once

#include "Support/Logger/LogDef.h"
#include "Core/Base.h"

#include <spdlog/fmt/bundled/base.h>

#define EVENT_TYPE(type)                                      \
    static VyEngine::EventType GetStaticType()                \
    {                                                         \
        return VyEngine::EventType::type;                     \
    }                                                         \

#define EVENT_CATEGORY(category)                                        \
    static uint8_t GetStaticCategory()                                  \
    {                                                                   \
        return static_cast<uint8_t>(VyEngine::EventCategory::category); \
    }


namespace VyEngine
{
    enum class EventType : uint8_t
    {
        None = 0,
        EngineClosed,
        WindowClosed, WindowMaximized, WindowMinimized, WindowResized, WindowRestored, WindowFocused, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseEntered
    };

    enum EventCategory : uint8_t
    {
        VY_NULL_EVENT         = 0,
        VY_ENGINE_EVENT       = BIT(0),
        VY_INPUT_EVENT        = BIT(1),
        VY_KEYBOARD_EVENT     = BIT(2),
        VY_MOUSE_EVENT        = BIT(3),
        VY_MOUSE_BUTTON_EVENT = BIT(4)
    };


    class Event
    {
    public:
        Event()          = default;
        virtual ~Event() = default;

        void SetHandled(bool value) { m_Handled = value; }
        bool IsHandled() const { return m_Handled; }

        void SetName(std::string_view name) { m_Name = name; }
        std::string_view GetName() const { return m_Name; }

        virtual EventType GetType() const    = 0;
        virtual int GetCategory() const      = 0;
        virtual std::string ToString() const = 0;
    
    protected:
        bool m_Handled { false };
        std::string m_Name {};
    };
}

