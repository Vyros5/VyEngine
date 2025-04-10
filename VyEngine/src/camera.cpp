#include "camera.hpp"


Camera::Camera(float aspectRatio, glm::vec3 position) :
    Aspect(aspectRatio), 
    Position(position),
	Target(glm::vec3 (0.0f, 0.0f, -1.0f)),
	Up(glm::vec3 (0.0f, 1.0f, 0.0f)),
    WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    Right(glm::vec3(1.0f, 0.0f, 0.0f)),
	Yaw(-90.0f),
	Pitch(0.0f),
	MoveSpeed(2.5f),
	Sensitivity(0.5f),
	Zoom(45.0f)
{
    
}

Camera::~Camera()
{
    
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Target, Up);
}

glm::mat4 Camera::getProjMatrix() const
{
    return glm::perspective(glm::radians(Zoom), Aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::getVPMatrix() const
{
    glm::mat4 view = getViewMatrix();
    glm::mat4 proj = getProjMatrix();
    glm::mat4 vp = proj * view;
    return vp;
}

void Camera::updateDirection(float dx, float dy)
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
    glm::vec3 dir;

    dir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    dir.y = sin(glm::radians(Pitch));
    dir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Target = glm::normalize(dir);

    Right = glm::normalize(glm::cross(Target, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Target));
}


void Camera::updatePosition(CameraDirection direction, double dt)
{

    float velocity = (float)dt * MoveSpeed;

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


void Camera::updateZoom(float dy)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f)
    { Zoom -= dy; }

    else if (Zoom < 1.0f) 
    { Zoom = 1.0f; }

    else
    { Zoom = 45.0f; }
}