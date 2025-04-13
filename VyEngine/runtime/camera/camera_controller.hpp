#pragma once

#include <glm/glm.hpp>
#include <cstdint>

#include "camera_base.hpp"
#include "perspec_camera.hpp"

namespace VyEngine
{
    enum class CameraType : uint8_t
    {
        PERSPECTIVE,
        ORTHOGRAPHIC,
        FRUSTRUM,
    };

    
    class CameraController
    {
        glm::vec3 mPosition;

        // Direction Vectors
        glm::vec3 mDir     = glm::vec3( 0.0f,  0.0f, -1.0f );
        glm::vec3 mTarget  = glm::vec3( 0.0f,  0.0f, -1.0f );
        glm::vec3 mRight   = glm::vec3( 1.0f,  0.0f,  0.0f );
        glm::vec3 mUp      = glm::vec3( 0.0f,  1.0f,  0.0f );

        glm::vec3 mWorldUp = glm::vec3( 0.0f,  1.0f,  0.0f );

        // Angle
        float mAngleV = 0.0f;
        float mAngleH = 0.0f;

        void submitMatrixProjChanges() const;
        void recalculateRotation();

        CameraType cameraType = CameraType::PERSPECTIVE;
        bool renderingEnabled = true;

    public:

        mutable CameraBase mCamera;

        CameraController();
        ~CameraController();

        template<typename T>
        T& getCamera();

        template<typename T>
        const T& getCamera() const;

        template<typename T>
        void setCamera(const T& camera);

        CameraType getCameraType() const;
        void setCameraType(CameraType type);


        const glm::mat4& getMatrix(const glm::vec3& position) const;
        const glm::mat4& getViewMatrix(const glm::vec3& position) const;
        const glm::mat4& getProjMatrix() const;

        glm::mat4 getStaticMatrix() const;
        glm::mat4 getStaticViewMatrix() const;

        glm::vec3 getDirection() const;
        const glm::vec3& getDirectionDenormalized() const;
        void setDirection(const glm::vec3& dir);

        glm::vec3 getDirectionUp() const;

        float getHorizontalAngle() const;
        float getVerticalAngle() const;

        CameraController& rotate(float angleH, float angleV);
        glm::vec2 getRotation() const;
        void setRotation(glm::vec2 newRotation);

        const glm::vec3& getTargetVector() const;
        const glm::vec3& getRightVector() const;
        const glm::vec3& getUpVector() const;

        void setTargetVector(const glm::vec3& target);
        void setRightVector(const glm::vec3& right);
        void setUpVector(const glm::vec3& up);
    };
}