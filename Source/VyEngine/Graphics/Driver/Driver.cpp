#include "Graphics/Driver/Driver.h"

#include "Core/Base.h"
#include "Support/Logger/LogDef.h"
#include "Graphics/API/OpenGL/GLBackend.hpp"


Scope<VyEngine::GFX::API::GLBackend> m_GraphicsBackend;

namespace VyEngine::GFX
{
    Driver::Driver(const DriverConfig& driverConfig)
    {
        m_GraphicsBackend = MakeScope<API::GLBackend>();

        m_GraphicsBackend->Init(driverConfig.debugMode);


        m_Vendor        = m_GraphicsBackend->GetVendor();
        m_Hardware      = m_GraphicsBackend->GetHardware();
        m_Version       = m_GraphicsBackend->GetVersion();
        m_ShaderVersion = m_GraphicsBackend->GetShadingLanguageVersion();

        VYINFO("[OpenGL Info]");
        VYINFO("- Vendor:     {0}", m_Vendor.c_str());
        VYINFO("- Hardware:   {0}", m_Hardware.c_str());
        VYINFO("- Version:    {0}", m_Version.c_str());
        VYINFO("- SL Version: {0}", m_ShaderVersion.c_str());
    }

    Driver::~Driver()
    {

    }

    // void Driver::OnFrameCompleted()
    // {

    // }

    void Driver::SetViewport(u32 X, u32 Y, u32 width, u32 height)
    {
        m_GraphicsBackend->SetViewport(X, Y, width, height);
    }

    void Driver::ClearBuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer, const Vec4& color)
    {
        if (colorBuffer) 
        { 
            m_GraphicsBackend->SetClearColor(color.x, color.y, color.z, color.w); 
        }

        m_GraphicsBackend->ClearBuffers(colorBuffer, depthBuffer, stencilBuffer);
    }


    // void Driver::Draw(u32 instances)
    // {

    // }

    std::string_view Driver::GetVendor() const { return m_Vendor; }

    std::string_view Driver::GetHardware() const { return m_Hardware; }

    std::string_view Driver::GetVersion() const { return m_Version; }

    std::string_view Driver::GetShaderVersion() const { return m_ShaderVersion; }
}