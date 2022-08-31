#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

#define MAX_FOV 180.0f
#define MIN_FOV 0.1f

#define PITCH_LIMIT 89.0f

enum class MovementDirection { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 view;
    glm::mat4 projection;

    int width;
    int height;

    float fov;
    float nearPlane;
    float farPlane;
    float ratio;

    float pitch;
    float yaw;

    float speed = 15.0f;
    float sensitivity = 0.2f;

public:
    Camera(int width, int height);
    ~Camera();


    // get vectors
    void updateVectors();

    glm::mat4 getMVP(glm::vec3 const& model);

    // private getters
    glm::vec3 getPosition() const { return this->position; }

    // private setters
    void setPosition(glm::vec3 position) { this->position = position; }
    void setFOV(float fov);
    void setClippingPlanes(float nearPlane, float farPlane);
    void setDimensions(int width, int height);

    // input functions
    void processKeyboard(Keys &keys, float deltaTime);
    void processMouseMovement(Cursor const& cursor);
};

#endif // CAMERA_H