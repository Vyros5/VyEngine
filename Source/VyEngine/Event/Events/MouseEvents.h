#pragma once

#include "Event/Event.hpp"
#include "Window/Data/EInput.h"

using namespace VyEngine::Window::Data;

namespace VyEngine::Events
{
    class MouseEvent : public VyEngine::Event
    {
    public:
        MouseEvent() = default;
        explicit MouseEvent(EMouseCode button) : m_Button(button) {}

        EMouseCode GetButton() const
        {
            return m_Button;
        }

        EVENT_CATEGORY(VY_MOUSE_EVENT | VyEngine::EventCategory::VY_INPUT_EVENT)

    protected:
        EMouseCode m_Button{0};
    };


    class MouseButtonPressedEvent : public MouseEvent
    {
    public:
        MouseButtonPressedEvent(EMouseCode button) : MouseEvent(button) {}

        EVENT_TYPE(MouseButtonPressed)

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
            return std::string("MouseButtonPressedEvent");
            // return fmt::format("MouseButtonPressedEvent : {0}", mButton);
        }
    };


    class MouseButtonReleasedEvent : public MouseEvent
    {
    public:
        explicit MouseButtonReleasedEvent(EMouseCode button) : MouseEvent(button) {}

        EVENT_TYPE(MouseButtonReleased)

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
            return std::string("MouseButtonReleasedEvent");
            // return fmt::format("MouseButtonReleasedEvent : {0}", mButton);
        }
    };


    class MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(double xpos, double ypos) : m_XPos(xpos), m_YPos(ypos) {}

        double GetPosX() const { return m_XPos; }

        double GetPosY() const { return m_YPos; }

        EVENT_TYPE(MouseMoved)

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
            return std::string("MouseMovedEvent");
            // return fmt::format("MouseMovedEvent");
        }

    private:
        double m_XPos{0};
        double m_YPos{0};
    };


    class MouseScrolledEvent : public MouseEvent
    {
    public:
        MouseScrolledEvent(double xOffset, double yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        double GetOffetX() const { return m_XOffset; }

        double GetOffetY() const { return m_YOffset; }

        EVENT_TYPE(MouseScrolled)

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
            return std::string("MouseScrolledEvent");
            // return fmt::format("MouseScrolledEvent : {0}", mButton);
        }

    private:
        double m_XOffset{0};
        double m_YOffset{0};
    };
}