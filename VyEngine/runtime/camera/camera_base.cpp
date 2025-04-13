#include "camera_base.hpp"

#include "logger/vy_logger.hpp"
#include "vy_macro.hpp"

namespace VyEngine
{
    const glm::mat4& CameraBase::getMatrix()     const
    {
        VY_ASSERT(this->updateProj == false);
        if (this->updateMatrix)
        {
            this->mMatrix = this->getProjMatrix() * this->getViewMatrix();
            // Set Culler
        }

        return this->mMatrix;
    }

    const glm::mat4& CameraBase::getViewMatrix() const
    {
        return this->mView;
    }

    const glm::mat4& CameraBase::getProjMatrix() const
    {
        return this->mProj;
    }

    const glm::vec2& CameraBase::getProjCenter() const
    {
        return this->mProjCenter;
    }


    void CameraBase::setViewMatrix(const glm::mat4& v)
    {
        this->mView = v;
        this->updateMatrix = true;
    }

    void CameraBase::setProjMatrix(const glm::mat4& v)
    {
        this->mProj = v;
        this->updateProj = false;
        this->updateMatrix = true;
    }

    void CameraBase::setProjCenter(const glm::vec2& v)
    {
        this->mProjCenter = v;
        this->updateProj = true;
    }


    float CameraBase::getZoom() const
    {
        return this->mZoom;
    }
    
    void  CameraBase::setZoom(float v)
    {
        this->mZoom = v;
        this->updateProj = true;
    }


    float CameraBase::getAspect() const
    {
        return this->mAspect;
    }

    void  CameraBase::setAspect(float w, float h)
    {
        this->setAspect(w / h);
    }

    void  CameraBase::setAspect(float v)
    {
        this->mAspect = v;
        this->updateProj = true;
    }


    float CameraBase::getZFar() const
    {
        return this->mZFar;
    }

    void  CameraBase::setZFar(float v)
    {
        this->mZFar = glm::max(v, this->mZNear);
        this->updateProj = true;
    }


    float CameraBase::getZNear() const
    {
        return this->mZNear;
    }

    void  CameraBase::setZNear(float v)
    {
        this->mZNear = glm::max(v, this->mZFar);
        this->updateProj = true;
    }

}