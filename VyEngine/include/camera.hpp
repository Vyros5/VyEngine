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
    glm::vec3 pos;

    // Camera Directions
    glm::vec3 Target;
    glm::vec3 Right;
    glm::vec3 Up;

    // Global Directions
    glm::vec3 worldUp;

    // Yaw Rotation (X-Axis)
    float yaw;

    // Pitch Rotation (Y-Axis)
    float pitch;

    // Movement Values
    float speed;
    float sensitivity;
    float zoom;

    float aspect;

    ProjData projectionData;

    bool firstLook = true;

    // Initialize with aspect and position.
    Camera(float aspectRatio, glm::vec3 position = glm::vec3(0.0f));
    
     ~Camera();

    // Get Matrices
    glm::mat4 getMatrix() const;
    glm::mat4 getViewMatrix() const { return getMatrix(); }
    glm::mat4 getProjMatrix() const;
    glm::mat4 getViewProjMatrix() const;

    const ProjData& getProjData() const { return projectionData; }

    const glm::vec3 getPos() const { return pos; }
    const glm::vec3& getTarget() const { return Target; }
    const glm::vec3& getUp() const { return Up; }

    void setPosition(float x, float y, float z);
    void setPosition(const glm::vec3 &pos);

    void setTarget(float x, float y, float z);
    void setTarget(const glm::vec3 &target);

    void setUp(float x, float y, float z) { Up.x = x; Up.y = y; Up.z = z; }
    void setUp(const glm::vec3 &up) { Up = up; }

    void updateDirection(float dx, float dy);

    void updatePosition(CameraDirection direction, double dt);

    void updateZoom(double dy);

    float getZoom();

    void updateCameraVectors();
};