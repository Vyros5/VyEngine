#pragma once
#include <glm/glm.hpp>
#include "VyLib/vy_core.hpp"
#include "camera/camera_controller.hpp"
#include "render/shader_program.hpp"
#include "render/base_renderer.hpp"

namespace VyEngine
{
    enum class BufferBitType 
    {
        Color,
        Depth,
        ColorDepth
    };

    class Renderer
    {
    private:
        glm::vec4 mClearColor { 0.2f, 0.2f, 0.2f, 1.0f };

        UniquePtr<BaseRenderer> mRendererAPI { nullptr };

    public:
        Renderer();

        void Init(const uint16_t width, const uint16_t height);
        void Shutdown();

        void BeginScene(SharedPtr<CameraController>& cameraController);

        void Submit(const SharedPtr<ShaderProgram>& shader);

        void EndScene();

        void EnableDepthTesting(bool enabled);
        void EnableDepthMask(bool enabled);
        void EnableFaceCulling(bool enabled);

        void ClearBufferBit(const BufferBitType bitType);
        void SetClearColor(const glm::vec4& color) { mClearColor = color; }
        const glm::vec4& GetClearColor() { return mClearColor; }

        void OnWindowResize(std::uint32_t width, std::uint32_t height);

        static BaseRenderer::API GetAPI() { return BaseRenderer::GetAPI(); }
    };
}