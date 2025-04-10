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

struct ProjectionInfo
{
    float FOV    = 0.0f;
    float Width  = 0.0f;
    float Height = 0.0f;
    float zNear  = 0.0f;
    float zFar   = 0.0f;
};

struct CameraSettings
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f);
    
    
    double yaw   = -90.0f;
    double pitch = 0.0f;

    double speed = 2.5f;
    double sensitivity = 0.5f;
    double zoom = 45.0f;

    float aspectRatio = 0.0f;
};

class Camera
{
public:

    // Name
    std::string Name;

	// Position
    glm::vec3 Position;

    // Camera Directions
    glm::vec3 Target;
    glm::vec3 Right;
    glm::vec3 Up;

    // Global Directions
    glm::vec3 WorldUp;

    // Yaw Rotation (X-Axis)
    double Yaw = 0.0f;
    double AngleH;

    // Pitch Rotation (Y-Axis)
    double Pitch = 0.0f;
    double AngleV;

    // Values
    double MoveSpeed = 0.0f;
    double Sensitivity = 0.0f;
    double Zoom = 0.0f;

    // Aspect Ratio
    float Aspect = 0.0f;

    bool FirstLook = true;

    // Initialize with projection data and position.
    Camera(CameraSettings settings);
    
    ~Camera() {};

    // Get Matrices
    glm::mat4 getViewMatrix()       const;
    glm::mat4 getProjMatrix()       const;
    glm::mat4 getVPMatrix()         const;

    const glm::vec3 getPosition()   const { return Position; }
    const glm::vec3 getTarget()     const { return Target; }
    const glm::vec3 getUp()         const { return Up; }

    const double getZoom()          const { return Zoom; }


    void setPosition(const glm::vec3 &pos)  { Position = pos; }
    void setTarget(const glm::vec3 &target) { Target = target; }
    void setUp(const glm::vec3 &up)         { Up = up; }


    void updateDirection(double dx, double dy);
    void updatePosition(CameraDirection direction, double dt);
    void updateZoom(double dy);
    void updateCameraVectors();

};