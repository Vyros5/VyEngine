#include "render/renderer.hpp"

// https://github.com/denyskryvytskyi/ElvenEngine/blob/4ac0f83fcb7248bb19f6bae50d77e60d65e93171/Engine/src/Renderer/Renderer.cpp

namespace VyEngine
{
    Renderer::Renderer() :
        mRendererAPI(BaseRenderer::Create())
    {}

    void Renderer::Init(const uint16_t width, const uint16_t height)
    {
        mRendererAPI->SetViewport(0, 0, width, height);

        mRendererAPI->Init();

    }
    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene(SharedPtr<CameraController>& cameraController)
    {
        mRendererAPI->EnableDepthTesting(true);
        mRendererAPI->SetClearColor(Renderer::GetClearColor());
        mRendererAPI->Clear();
    }


    void Renderer::EndScene()
    {
        // 1. Skybox
        // 2. Render Pass: 
        // 3. Render Pass: Post-Processing.
        // 4. Render Pass: Draw on screen.

        // - Bind fbo
        mRendererAPI->EnableDepthTesting(false);
        mRendererAPI->SetClearColor(Renderer::GetClearColor());
        mRendererAPI->ClearColorBit();
    }


    void Renderer::Submit(const SharedPtr<ShaderProgram>& shader)
    {

    }



    void Renderer::EnableDepthTesting(bool enabled)
    {
        mRendererAPI->EnableDepthTesting(enabled);
    }

    void Renderer::EnableDepthMask(bool enabled)
    {
        mRendererAPI->EnableDepthMask(enabled);
    }

    void Renderer::EnableFaceCulling(bool enabled)
    {
        mRendererAPI->EnableFaceCulling(enabled);
    }

    void Renderer::ClearBufferBit(const BufferBitType bitType)
    {
        if (bitType == BufferBitType::Color)
        {
            mRendererAPI->ClearColorBit();
        }
        else
        {
            mRendererAPI->Clear();
        }
    }
}