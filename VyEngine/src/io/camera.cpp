#include "io/camera.hpp"


Camera::Camera(float aspectRatio, glm::vec3 position) :
    Target(glm::vec3 (0.0f, 0.0f, -1.0f)),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    Right(glm::vec3(1.0f, 0.0f, 0.0f)),
    Up(glm::vec3 (0.0f, 1.0f, 0.0f)),
    aspect(aspectRatio),
    sensitivity(0.5f),
    pos(position),
	yaw(-90.0f),
	pitch(0.0f),
	speed(2.5f),
	zoom(45.0f)
{

}

Camera::~Camera()
{
    
}

glm::mat4 Camera::getMatrix() const
{
    return glm::lookAt(pos, pos + Target, Up);
}

glm::mat4 Camera::getProjMatrix() const
{
    return glm::perspective(glm::radians(zoom), aspect, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewProjMatrix() const
{
    glm::mat4 view = getViewMatrix();
    glm::mat4 proj = getProjMatrix();
    glm::mat4 vp = proj * view;
    return vp;
}

void Camera::updateDirection(float dx, float dy)
{
    // Apply sensitivity.
    dx *= sensitivity;
    dy *= sensitivity;

    // Apply change to yaw & pitch.
    yaw   += dx;
    pitch += dy;
    
    // Lock pitch rotation.
    if (pitch >  89.0f) 
        pitch =  89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    // Update Vectors.
    updateCameraVectors();
}

// Change camera directional vectors based on movement.
void Camera::updateCameraVectors()
{
    glm::vec3 dir;

    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Target = glm::normalize(dir);

    Right = glm::normalize(glm::cross(Target, worldUp));
    Up    = glm::normalize(glm::cross(Right, Target));
}

void Camera::updatePosition(CameraDirection direction, double dt)
{
    float velocity = (float)dt * speed;

    switch (direction) 
    {
        case CameraDirection::FORWARD:
            pos += Target * velocity;
            break;

        case CameraDirection::BACKWARD:
            pos -= Target * velocity;
            break;

        case CameraDirection::RIGHT:
            pos += Right * velocity;
            break;

        case CameraDirection::LEFT:
            pos -= Right * velocity;
            break;

        case CameraDirection::UP:
            pos += Up * velocity;
            break;

        case CameraDirection::DOWN:
            pos -= Up * velocity;
            break;
    }
}

// get zoom value for camera
float Camera::getZoom() 
{
    return zoom;
}


void Camera::updateZoom(double dy)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
    {
        zoom -= dy;
    }
    else if (zoom < 1.0f) 
    {
        zoom = 1.0f;
    }
    else
    { 
        zoom = 45.0f;
    }
}