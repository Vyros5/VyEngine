#pragma once

#include "Support/Logger/LogDef.h"

#include "Core/Base.h"
#include "defines.h"

#include <functional>
#include <unordered_map>
#include <ostream>



namespace VyEngine::Evt
{
	/**
	* The ID of a listener (Registered callback).
	* This value is needed to remove a listener from an event
	*/
    using ListenerID = u64;

	/**
	* A simple event that contains a set of function callbacks. These functions will be called on invoke
	*/
    template<class... ArgTypes>
    class Event
    {
    public:
        /**
        * Simple shortcut for a generic function without return value
        */
        using Callback = std::function<void(ArgTypes...)>;

        /**
        * Add a function callback to this event
        * Also return the ID of the new listener (You should store the returned ID if you want to remove the listener later)
        * @param p_call
        */
        ListenerID AddListener(Callback p_callback);

        /**
        * Add a function callback to this event
        * Also return the ID of the new listener (You should store the returned ID if you want to remove the listener later)
        * @param p_call
        */
        ListenerID operator+=(Callback p_callback);

        /**
        * Remove a function callback to this event using a Listener (Created when calling AddListener)
        * @param p_listener
        */
        bool RemoveListener(ListenerID p_listenerID);

        /**
        * Remove a function callback to this event using a Listener (Created when calling AddListener)
        * @param p_listener
        */
        bool operator-=(ListenerID p_listenerID);

        /**
        * Remove every listeners to this event
        */
        void RemoveAllListeners();

        /**
        * Return the number of callback registered
        */
        uint64_t GetListenerCount();

        /**
        * Call every callbacks attached to this event
        * @param p_args (Variadic)
        */
        void Invoke(ArgTypes... p_args);

    private:
        std::unordered_map<ListenerID, Callback>	m_callbacks;
        ListenerID									m_availableListenerID = 0;
    };
}


#include "Event/Event.inl"






// namespace VyEngine
// {
//     // Events in VyEngine are currently blocking, meaning when an event occurs
// 	// it immediately gets dispatched and must be dealt with right then an there.
// 	// For the future, a better strategy might be to buffer events in an event
// 	// bus and process them during the "event" part of the update stage.


//     enum class EventType : u8
//     {
// 		None = 0,
// 		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
// 		AppTick, AppUpdate, AppRender,
// 		KeyPressed, KeyReleased, KeyTyped,
// 		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
//     };

//     enum EventCategory : i32
//     {
//         VY_NULL_EVENT         = 0,
//         VY_APP_EVENT          = BIT(0),
//         VY_INPUT_EVENT        = BIT(1),
//         VY_KEYBOARD_EVENT     = BIT(2),
//         VY_MOUSE_EVENT        = BIT(3),
//         VY_MOUSE_BUTTON_EVENT = BIT(4)
//     };

// #define EVENT_TYPE(type)                                                \
//     static EventType GetStaticType()                                    \
//     {                                                                   \
//         return EventType::type;                                         \
//     }                                                                   \
//     virtual EventType GetEventType() const override                     \
//     {                                                                   \
//         return GetStaticType();                                         \
//     }                                                                   \
//     virtual const char* GetName() const override                        \
//     {                                                                   \
//         return #type;                                                   \
//     }                                                                   \
    
// #define EVENT_CATEGORY(category)                                        \
//     virtual i32 GetCategoryFlags() const override                       \
//     {                                                                   \
//         return category;                                                \
//     }

//     class Event
//     {
//     public:
//         virtual ~Event() = default;

//         bool Handled = false;

//         [[nodiscard]] virtual EventType GetEventType() const   = 0;
//         [[nodiscard]] virtual i32 GetCategoryFlags() const     = 0;
//         [[nodiscard]] virtual const char* GetName() const = 0;
//         [[nodiscard]] virtual VyString ToString() const { return GetName(); }

//         [[nodiscard]] bool IsInCategory(EventCategory category) const { return GetCategory() & category; }
//     };


//     class EventDispatcher
//     {
//     public:
//         explicit EventDispatcher(Event& event) : m_Event(event) {}

//         template<typename T, typename F>
//         bool Dispatch(const F& func)
//         {
//             if (m_Event.GetEventType() == T::GetStaticType())
//             {
//                 m_Event.Handled |= func(static_cast<T&>(m_Event));

//                 VYINFO("[Dispatcher] Event Handled: {0}", m_Event.ToString());
//                 return true;
//             }

//             return false;
//         }

//     private:
// 		Event& m_Event;
//     };

//     inline std::ostream& operator<<(std::ostream& os, const Event& e)
// 	{
// 		return os << e.ToString();
// 	}
// }
    

    

// #define EVENT_TYPE(type)                                                
//     static VyEngine::EventType GetStaticType()                          
//     {                                                                   
//         return VyEngine::EventType::type;                               
//     }                                                                   

// #define EVENT_CATEGORY(category)                                        
//     static u8 GetStaticCategory()                                       
//     {                                                                   
//         return static_cast<u8>(VyEngine::EventCategory::category);      
//     }

    // class Event
    // {
    // public:
    //     // Event()          = default;
    //     virtual ~Event() = default;

    //     bool isHandled = false;

    //     void SetHandled(bool value) { m_Handled = value; }
    //     bool IsHandled() const { return m_Handled; }

    //     void SetName(VyStringView name) { m_Name = name; }
    //     VyStringView GetName() const { return m_Name; }

    //     virtual EventType GetEventType() const = 0;
    //     virtual i32 GetCategory() const   = 0;
    //     virtual VyString ToString() const = 0;
    
    // protected:
    //     VyString m_Name {};
    // };

