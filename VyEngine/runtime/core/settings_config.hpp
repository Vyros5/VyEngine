#pragma once

#include <cstdint>
#include <iostream>

namespace VyEngine
{
    class SettingsConfig
    {
    public:
        void Load();
        void Save();

        uint16_t winWidth  = 1280;
        uint16_t winHeight = 720;

        bool enableFullscreen = false;
        bool enableVSync = false;

    };

    extern SettingsConfig gEngineSettings;
}