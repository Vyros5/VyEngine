#pragma once

namespace VyEngine::Window::Data
{
    struct WindowData
    {
    public:
        const char*  Title        {   };
        unsigned int Width        { 0 };
        unsigned int Height       { 0 };
        int          Dpi          { 0 };
        float        DpiScale     { 0.0f  };
        float        AspectRatio  { 0.0f  };
        bool         IsVSync      { false };
        bool         IsFullscreen { false };
        bool         IsHidden     { false };
        bool         IsVisible    { true  };
        bool         IsMaximized  { false };
        bool         IsMinimized  { false };
        bool         IsFocused    { true  };
        bool         IsResizable  { true  };
        bool         IsDecorated  { true  };

        std::function<void(Event&)> CallbackFn;

    public:
        WindowData(unsigned int width = 1280, unsigned int height = 720, const char* title = "VyEngine") : Width(width), Height(height)
        {
            this->Title = title;
            UpdateAspectRatio();
        }

        ~WindowData() = default;

        void SetWidth(unsigned int w)
        {
            Width = w;
            UpdateAspectRatio();
        }

        void SetHeight(unsigned int h)
        {
            Height = h;
            UpdateAspectRatio();
        }

    private:
        void UpdateAspectRatio()
        {
            AspectRatio = (float)Width / (float)Height;
        }
    };
}