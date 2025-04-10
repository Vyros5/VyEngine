#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

enum class CameraDirection
{
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:

	// Position
    glm::vec3 Position;

    // Camera Directions
    glm::vec3 Target;
    glm::vec3 Right;
    glm::vec3 Up;

    // Global Directions
    glm::vec3 WorldUp;

    // Yaw Rotation (X-Axis)
    float Yaw;

    // Pitch Rotation (Y-Axis)
    float Pitch;

    // Values
    float MoveSpeed;
    float Sensitivity;
    float Zoom;

    // Aspect Ratio
    float Aspect;

    bool FirstLook = true;

    // Initialize with projection data and position.
    Camera(float aspectRatio, glm::vec3 position = glm::vec3(0.0f));
    
    ~Camera();

    // Get Matrices
    glm::mat4 getViewMatrix()       const;
    glm::mat4 getProjMatrix()       const;
    glm::mat4 getVPMatrix()         const;

    const glm::vec3 getPosition()   const { return Position; }
    const glm::vec3 getTarget()     const { return Target; }
    const glm::vec3 getUp()         const { return Up; }

    const float getZoom()          const { return Zoom; }


    void setPosition(const glm::vec3 &pos)  { Position = pos; }
    void setTarget(const glm::vec3 &target) { Target = target; }
    void setUp(const glm::vec3 &up)         { Up = up; }


    void updateDirection(float dx, float dy);
    void updatePosition(CameraDirection direction, double dt);
    void updateZoom(float dy);
    void updateCameraVectors();
};