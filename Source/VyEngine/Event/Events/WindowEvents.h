#pragma once

#include "Event/Event.hpp"

namespace VyEngine::Events
{
    class WindowClosedEvent : public VyEngine::Event
    {
    public:
        WindowClosedEvent()
        {
            m_Name = "WindowClosed";
        }
        
        ~WindowClosedEvent() = default;

        VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        int GetCategory() const override
        {
            return GetStaticCategory();
        }

        std::string ToString() const override
        {
            return std::string("WindowClosedEvent");
            // return fmt::format("WindowClosedEvent");
        }

        EVENT_TYPE(WindowClosed)
        EVENT_CATEGORY(VY_ENGINE_EVENT)
    };


    class WindowMaximizedEvent : public VyEngine::Event
    {
    public:
        WindowMaximizedEvent()
        {
            m_Name = "WindowMaximized";
        }

        ~WindowMaximizedEvent() = default;

        VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        int GetCategory() const override
        {
            return GetStaticCategory();
        }

        std::string ToString() const override
        {
            return std::string("WindowMaximizedEvent");
            // return fmt::format("WindowMaximizedEvent");
        }

        EVENT_TYPE(WindowMaximized)
        EVENT_CATEGORY(VY_ENGINE_EVENT)
    };


    class WindowMinimizedEvent : public VyEngine::Event
    {
    public:
        WindowMinimizedEvent()
        {
            m_Name = "WindowMinimized";
        }
        ~WindowMinimizedEvent() = default;

        VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        int GetCategory() const override
        {
            return GetStaticCategory();
        }

        std::string ToString() const override
        {
            return std::string("WindowMinimizedEvent");
            // return fmt::format("WindowMinimizedEvent");
        }

        EVENT_TYPE(WindowMinimized)
        EVENT_CATEGORY(VY_ENGINE_EVENT)
    };


    class WindowResizedEvent : public VyEngine::Event
    {
    public:
        WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height)
        {
            m_Name = "WindowResized";
        }

        ~WindowResizedEvent() = default;

        unsigned int GetWidth() const   { return m_Width; }
        unsigned int GetHeight() const  { return m_Height; }

        void SetWidth(unsigned int value)  { m_Width  = value; }
        void SetHeight(unsigned int value) { m_Height = value; }

        VyEngine::EventType GetType() const override { return GetStaticType(); }

        int GetCategory() const override { return GetStaticCategory(); }

        std::string ToString() const override
        {
            return std::string("WindowResizeEvent");
            // return fmt::format("WindowResizeEvent X: {0}, Y: {1}", m_Width, m_Height);
        }

        EVENT_TYPE(WindowResized)
        EVENT_CATEGORY(VY_ENGINE_EVENT)

    private:
        unsigned int m_Width{0};
        unsigned int m_Height{0};
    };


    class WindowRestoredEvent : public VyEngine::Event
    {
    public:
        WindowRestoredEvent()
        {
            m_Name = "WindowRestored";
        }
        ~WindowRestoredEvent() = default;

        VyEngine::EventType GetType() const override
        {
            return GetStaticType();
        }

        int GetCategory() const override
        {
            return GetStaticCategory();
        }

        std::string ToString() const override
        {
            return std::string("WindowRestoredEvent");
            // return fmt::format("WindowRestoredEvent");
        }

        EVENT_TYPE(WindowRestored)
        EVENT_CATEGORY(VY_ENGINE_EVENT)
    };
}