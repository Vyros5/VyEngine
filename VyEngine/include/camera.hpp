#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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


struct ProjData
{
   float FOV    = 0.0f;
   float Width  = 0.0f;
   float Height = 0.0f;
   float zNear  = 0.0f;
   float zFar   = 0.0f;
};


class Camera
{
public:

	// Position
    glm::vec3 Position = glm::vec3(0.0f);

    // Camera Directions
    glm::vec3 Target = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Right  = glm::vec3(1.0f, 0.0f,  0.0f);
    glm::vec3 Up     = glm::vec3(0.0f, 1.0f,  0.0f);

    // Global Directions
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Yaw Rotation (X-Axis)
    double Yaw = -90.0;

    // Pitch Rotation (Y-Axis)
    double Pitch = 0.0;

    // Values
    double MoveSpeed = 2.5;
    double Sensitivity = 0.5;
    double Zoom = 45.0;

    // Aspect Ratio
    float Aspect;

    ProjData ProjectionData;

    bool FirstLook = true;

    // Initialize with projection data and position.
    Camera(float aspectRatio, glm::vec3 position = glm::vec3(0.0f));
    
    ~Camera();

    // Get Matrices
    glm::mat4 getMatrix()           const;
    glm::mat4 getViewMatrix()       const { return getMatrix(); }
    glm::mat4 getProjMatrix()       const;
    glm::mat4 getVPMatrix()         const;

    const ProjData& getProjData()   const { return ProjectionData; }

    const glm::vec3 getPosition()   const { return Position; }
    const glm::vec3 getTarget()     const { return Target; }
    const glm::vec3 getUp()         const { return Up; }

    const double getZoom()          const { return Zoom; }


    void setPosition(const glm::vec3 &pos)  { Position = pos; }
    void setTarget(const glm::vec3 &target) { Target = target; }
    void setUp(const glm::vec3 &up)         { Up = up; }


    void updateCameraVectors();
    void updateZoom(double dy);
    void updateDirection(double dx, double dy);
    void updatePosition(CameraDirection direction, double dt);
};