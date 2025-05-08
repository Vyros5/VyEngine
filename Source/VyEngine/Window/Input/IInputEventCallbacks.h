// #pragma once

// #include "Event/Events/WindowEvents.h"
// #include "Event/Events/MouseEvents.h"
// #include "Event/Events/KeyEvents.h"

// namespace VyEngine::Inputs
// {
//     struct IMouseEventCallback
//     {
//         virtual bool OnMouseMoved(Events::MouseMovedEvent&)                   = 0;
//         virtual bool OnMouseScrolled(Events::MouseScrolledEvent&)             = 0;
//         virtual bool OnMouseButtonPressed(Events::MouseButtonPressedEvent&)   = 0;
//         virtual bool OnMouseButtonReleased(Events::MouseButtonReleasedEvent&) = 0;
//     };
    
    
//     struct IKeyboardEventCallback
//     {
//         virtual bool OnKeyPressed(Events::KeyPressedEvent&)   = 0;
//         virtual bool OnKeyReleased(Events::KeyReleasedEvent&) = 0;
//         virtual bool OnKeyTyped(Events::KeyTypedEvent&)       = 0;
//     };


//     struct IWindowEventCallback
//     {
//         virtual bool OnWindowClosed(Events::WindowClosedEvent&)       = 0;
//         virtual bool OnWindowResized(Events::WindowResizedEvent&)     = 0;
//         virtual bool OnWindowRestored(Events::WindowRestoredEvent&)   = 0;
//         virtual bool OnWindowMinimized(Events::WindowMinimizedEvent&) = 0;
//         virtual bool OnWindowMaximized(Events::WindowMaximizedEvent&) = 0;
//     };
// }