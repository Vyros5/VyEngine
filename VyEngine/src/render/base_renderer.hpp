#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include "VyLib/vy_core.hpp"

namespace VyEngine
{
    class BaseRenderer
    {
    public:
        enum class API
        {
            None   = 0,
            OpenGL = 1,
        };

    public:
        virtual ~BaseRenderer() = default;

        virtual void Init() = 0;
        virtual void SetViewport(std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h) = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void ClearColorBit() = 0;

        virtual void EnableDepthTesting(bool enabled) = 0;
        virtual void EnableDepthMask(bool enabled) = 0;
        virtual void EnableFaceCulling(bool enabled) = 0;

        static API GetAPI() { return s_API; }
        static UniquePtr<BaseRenderer> Create();

    private:
        static API s_API;
    };
}