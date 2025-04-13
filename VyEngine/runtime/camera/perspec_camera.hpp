#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>


#include "camera_base.hpp"

namespace VyEngine
{
    class PerspectiveCamera : CameraBase
    {
    public:
        
        static constexpr float mDefaultFOV = 65.0f;

        void setFOV(float angle);
        float getFOV() const;
    };
}