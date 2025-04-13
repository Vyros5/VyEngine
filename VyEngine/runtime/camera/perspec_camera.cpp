#include "perspec_camera.hpp"


namespace VyEngine
{
    void PerspectiveCamera::setFOV(float angle)
    {
        this->setZoom(angle / mDefaultFOV);
        this->setProjMatrix(
            glm::perspective(
                glm::radians(this->getFOV()), 
                this->getAspect(),
                this->getZNear(),
                this->getZFar()
            )
        );
    }

    float PerspectiveCamera::getFOV() const
    {
        return this->getZoom() * mDefaultFOV;
    }
}