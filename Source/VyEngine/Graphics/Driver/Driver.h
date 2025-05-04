#pragma once

#include <glm/glm.hpp>
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

        void SetViewport(uint32_t X, uint32_t Y, uint32_t width, uint32_t height);


        void ClearBuffer(
            bool colorBuffer,
			bool depthBuffer,
			bool stencilBuffer,
            const glm::vec4& color = glm::vec4(0.35f, 0.35f, 0.35f, 1.0f)
        );

        void Draw(uint32_t instances);


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