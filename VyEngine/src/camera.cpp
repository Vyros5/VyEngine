#include "camera.hpp"


// Aspect(aspectRatio), 
// Position(position),
// Target(glm::vec3 (0.0f, 0.0f, -1.0f)),
// Up(glm::vec3 (0.0f, 1.0f, 0.0f)),
// WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
// Right(glm::vec3(1.0f, 0.0f, 0.0f)),
// Yaw(-90.0f),
// Pitch(0.0f),
// MoveSpeed(2.5f),
// Sensitivity(0.5f),
// Zoom(45.0f)

Camera::Camera(CameraSettings settings)
{
    Position    = settings.position;
    Target      = settings.target;
    Right       = settings.right;
    Up          = settings.up;
    WorldUp     = glm::vec3(0.0f, 1.0f, 0.0f);

    Yaw         = settings.yaw;
    Pitch       = settings.pitch;

    MoveSpeed   = settings.speed;
    Sensitivity = settings.sensitivity;
    Zoom        = settings.zoom;

    Aspect      = settings.aspectRatio;
}


glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Target, Up);
}

glm::mat4 Camera::getProjMatrix() const
{
    return glm::perspective(glm::radians(Zoom), (double)Aspect, 0.1, 1000.0);
}

glm::mat4 Camera::getVPMatrix() const
{
    glm::mat4 view = getViewMatrix();
    glm::mat4 proj = getProjMatrix();
    glm::mat4 vp = proj * view;
    return vp;
}

void Camera::updateDirection(double dx, double dy)
{
    // Apply sensitivity.
    dx *= Sensitivity;
    dy *= Sensitivity;

    // Apply change to yaw & pitch.
    Yaw   += dx;
    Pitch += dy;
    
    // Lock pitch rotation.
    if (Pitch >  89.0f) 
        Pitch =  89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;
    
    // Update Vectors.
    updateCameraVectors();
}

// Change camera directional vectors based on movement.
void Camera::updateCameraVectors()
{
    glm::dvec3 dir;

    dir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    dir.y = sin(glm::radians(Pitch));
    dir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Target = glm::normalize(dir);

    Right = glm::normalize(glm::cross(Target, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Target));
}


void Camera::updatePosition(CameraDirection direction, double dt)
{

    float velocity = (float)dt * static_cast<float>(MoveSpeed);

    switch (direction) 
    {
        case CameraDirection::FORWARD:
            Position += Target * velocity;
            break;

        case CameraDirection::BACKWARD:
            Position -= Target * velocity;
            break;

        case CameraDirection::RIGHT:
            Position += Right * velocity;
            break;

        case CameraDirection::LEFT:
            Position -= Right * velocity;
            break;

        case CameraDirection::UP:
            Position += Up * velocity;
            break;

        case CameraDirection::DOWN:
            Position -= Up * velocity;
            break;
    }
}


void Camera::updateZoom(double dy)
{
    if (Zoom >= 1.0 && Zoom <= 45.0)
    { Zoom -= dy; }

    else if (Zoom < 1.0) 
    { Zoom = 1.0; }

    else
    { Zoom = 45.0; }
}