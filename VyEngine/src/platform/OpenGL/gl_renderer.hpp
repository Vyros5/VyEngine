#pragma once

#include "render/base_renderer.hpp"

namespace VyEngine
{
    class OpenGLRenderer : public BaseRenderer
    {
        void Init() override;
        void SetViewport(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h) override;
        
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void ClearColorBit() override;

        void EnableDepthTesting(bool enabled) override;
        void EnableDepthMask(bool enabled) override;
        void EnableFaceCulling(bool enabled) override;
    };
}