#pragma once

#include <glm/glm.hpp>


namespace VyEngine
{
    class CameraBase
    {
    private:
        
        float mZNear = 0.1f;
        float mZFar  = 100.0f;

        float mZoom = 1.0f;
        float mAspect = 16.0f / 9.0f;
        
        glm::mat4 mView = glm::mat4(0.0f);
        glm::mat4 mProj = glm::mat4(0.0f);

        glm::vec2 mProjCenter{-0.5f};

        mutable glm::mat4 mMatrix{0.0f};
        mutable bool updateMatrix = true;

    public:

        mutable bool updateProj = true;
        
        const glm::mat4& getMatrix()     const;
        const glm::mat4& getViewMatrix() const;
        const glm::mat4& getProjMatrix() const;
        const glm::vec2& getProjCenter() const;

        void setViewMatrix(const glm::mat4& v);
        void setProjMatrix(const glm::mat4& v);
        void setProjCenter(const glm::vec2& v);

        float getZoom() const;
        void  setZoom(float v);

        float getAspect() const;
        void  setAspect(float w, float h);
        void  setAspect(float v);

        float getZFar() const;
        void  setZFar(float v);

        float getZNear() const;
        void  setZNear(float v);
        

    };
}