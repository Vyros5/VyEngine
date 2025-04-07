#include "io/camera.hpp"


Camera::Camera(float aspectRatio, glm::vec3 position) :
    Target(glm::vec3 (0.0f, 0.0f, -1.0f)),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    Right(glm::vec3(1.0f, 0.0f, 0.0f)),
    Up(glm::vec3 (0.0f, 1.0f, 0.0f)),
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