#pragma once

#include "defines.h"
#include <string>
#include <array>
#include <memory>

namespace VyEngine::GFX
{
    struct DriverConfig
    {
        bool debugMode = false;
    };

    /// @brief Handles the lifecycle of the graphics context
    class Driver final
    {
    public:
        Driver(const DriverConfig& driverConfig);

        ~Driver();

        /// @brief Notifies the driver that the frame is finished
        // void OnFrameCompleted();

        void SetViewport(u32 X, u32 Y, u32 width, u32 height);


        void ClearBuffer(
            bool colorBuffer,
			bool depthBuffer,
			bool stencilBuffer,
            const Vec4& color = Vec4(0.35f, 0.35f, 0.35f, 1.0f)
        );

        // void Draw(u32 instances);


        std::string_view GetVendor() const;
        std::string_view GetHardware() const;
        std::string_view GetVersion() const;
        std::string_view GetShaderVersion() const;


    private:
        std::string m_Vendor;
        std::string m_Hardware;
        std::string m_Version;
        std::string m_ShaderVersion;
    };
}