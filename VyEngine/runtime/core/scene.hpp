#pragma once

#include "VyLib/vy_core.hpp"
#include "camera/camera_controller.hpp"
#include "render/shader_program.hpp"


namespace VyEngine
{
    class Renderer
    {
    public:
        
        Renderer();

        void Init();

        void Shutdown();

        void Begin(SharedPtr<CameraController>& cameraController);

        void Submit(const SharedPtr<ShaderProgram>& shader);
    };
}