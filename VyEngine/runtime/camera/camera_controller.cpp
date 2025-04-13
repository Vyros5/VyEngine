#include "camera_controller.hpp"
#include "vy_macro.hpp"

namespace VyEngine
{
    template<>
    PerspectiveCamera& CameraController::getCamera<PerspectiveCamera>()
    {
        VY_ASSERT(this->getCameraType() == CameraType::PERSPECTIVE);
        static_assert(AssertEquality<sizeof(PerspectiveCamera), sizeof(this->mCamera)>::value, "Camera byte storage mismatch.");
        return *reinterpret_cast<PerspectiveCamera*>(&this->mCamera); // -V717
    }

    template<>
    const PerspectiveCamera& CameraController::getCamera<PerspectiveCamera>() const
    {
        VY_ASSERT(this->getCameraType() == CameraType::PERSPECTIVE);
        static_assert(AssertEquality<sizeof(PerspectiveCamera), sizeof(this->mCamera)>::value, "Camera byte storage mismatch. (const)");
        return *reinterpret_cast<PerspectiveCamera*>(&this->mCamera); // -V717
    }

    template<>
    void CameraController::setCamera<PerspectiveCamera>(const PerspectiveCamera& camera)
    {
        this->setCameraType(CameraType::PERSPECTIVE);
        this->getCamera<PerspectiveCamera>() = camera;
    }


    CameraController::CameraController()
    {
        this->setCameraType(CameraType::PERSPECTIVE);


    }

    CameraController::~CameraController()
    {

    }

    CameraType CameraController::getCameraType() const
    {
        return this->cameraType;
    }

    void CameraController::setCameraType(CameraType type)
    {
        this->cameraType = type;
        this->mCamera.setZoom(1.0f);
    }

    const glm::mat4& CameraController::getMatrix(const glm::vec3& position) const
    {
        if (this->mCamera.updateProj) { this->submitMatrixProjChanges(); }
        (void)this->getViewMatrix(position);

        return this->mCamera.getMatrix();
    }

    const glm::mat4& CameraController::getViewMatrix(const glm::vec3& position) const
    {
        glm::mat4 view = glm::lookAt(position, position + this->getDirection(), this->getUpVector());
        this->mCamera.setViewMatrix(view);

        return this->mCamera.getViewMatrix();
    }

    const glm::mat4& CameraController::getProjMatrix() const
    {
        if (this->mCamera.updateProj) { this->submitMatrixProjChanges(); }

        return this->mCamera.getProjMatrix();
    }


    glm::mat4 CameraController::getStaticMatrix() const
    {
        if (this->mCamera.updateProj) { this->submitMatrixProjChanges(); }

        glm::mat4 viewMatrix = this->getStaticViewMatrix();
        const glm::mat4 projMatrix = this->getProjMatrix();

        return projMatrix * viewMatrix;
    }

    glm::mat4 CameraController::getStaticViewMatrix() const
    {
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f), this->getDirection(), this->getUpVector());
        this->mCamera.setViewMatrix(view);

        glm::mat3 viewMatrix = (glm::mat3)this->mCamera.getViewMatrix();
        return (glm::mat4)viewMatrix;
    }


    void CameraController::submitMatrixProjChanges() const
    {
        if (this->getCameraType() == CameraType::PERSPECTIVE)
        {
            auto* cam = reinterpret_cast<PerspectiveCamera*>(&this->mCamera); // -V717
            auto fov = cam->getFOV();
            cam->setFOV(fov);
        }
    }

    void CameraController::recalculateRotation()
    {
        auto normDir = this->getDirection();
        float angleV = std::asin(normDir.y);
        float angleH = std::acos(glm::dot(normDir, glm::vec3(0.0f, 0.0f, 1.0f)));

        auto x = std::sin(angleH);
        auto z = std::cos(angleH);

        bool xCorrect = std::signbit(normDir.x) == std::signbit(x);
        bool zCorrect = std::signbit(normDir.z) == std::signbit(z);
        if (!xCorrect || !zCorrect)
        {
            angleH = glm::two_pi<float>() - angleH;
        }

        this->mAngleH = angleH;
        this->mAngleV = angleV;
    }


    glm::vec3 CameraController::getDirection() const
    {
        return glm::normalize(this->mDir);
    }

    const glm::vec3& CameraController::getDirectionDenormalized() const
    {
        return this->mDir;
    }

    void CameraController::setDirection(const glm::vec3& dir)
    {
        this->mDir = dir + glm::vec3(0.0f, 0.0f, 0.00001f);
        this->recalculateRotation();
    }

    glm::vec3 CameraController::getDirectionUp() const
    {
        return glm::cross(this->getDirection(), this->mRight);
    }

    float CameraController::getHorizontalAngle() const
    {
        return this->mAngleH;
    }

    float CameraController::getVerticalAngle() const
    {
        return this->mAngleV;
    }

    CameraController& CameraController::rotate(float angleH, float angleV)
    {
        angleH = glm::radians(angleH);
        angleV = glm::radians(angleV);

        this->mAngleH += angleH;
        this->mAngleV += angleV;

        this->mAngleV = glm::clamp(
            this->mAngleV, 
            -glm::half_pi<float>() + 0.001f,
             glm::half_pi<float>() - 0.001f
        );

        this->mAngleH = this->mAngleH - glm::two_pi<float>() * std::floor(this->mAngleH / glm::two_pi<float>());

        this->mDir = glm::vec3(
            std::cos(angleV) * std::sin(angleH),
            std::sin(angleV),
            std::cos(angleV) * std::cos(angleH)
        );

        this->mTarget = glm::vec3(
            sin(angleH),
            0.0f,
            cos(angleH)
        );

        this->mRight = glm::vec3(
            sin(angleH - glm::half_pi<float>()),
            0.0f,
            cos(angleH - glm::half_pi<float>())
        );

        return *this;
    }

    glm::vec2 CameraController::getRotation() const
    {
        return glm::vec2(glm::degrees(this->mAngleH), glm::degrees(this->mAngleV));
    }
    
    void CameraController::setRotation(glm::vec2 newRotation)
    {
        auto oldRotation = this->getRotation();
        newRotation.x = std::fmod(newRotation.x - oldRotation.x, 360.0f);
        newRotation.y = std::fmod(newRotation.y - oldRotation.y, 360.0f);

        this->rotate(newRotation.x, newRotation.y);
    }

    const glm::vec3& CameraController::getTargetVector() const
    {
        return this->mTarget;
    }
    const glm::vec3& CameraController::getRightVector() const
    {
        return this->mRight;
    }
    const glm::vec3& CameraController::getUpVector() const
    {
        return this->mUp;
    }

    void CameraController::setTargetVector(const glm::vec3& target)
    {
        this->mTarget = target;
    }
    void CameraController::setRightVector(const glm::vec3& right)
    {
        this->mRight = right;
    }
    void CameraController::setUpVector(const glm::vec3& up)
    {
        this->mUp = up;
    }
}