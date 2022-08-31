#include "camera.h"

Camera::Camera(int width, int height) :
    position(glm::vec3(1.0f, 1.0f, 1.0f)),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    fov(75.0f),
    nearPlane(0.01f),
    farPlane(10.0f),
    pitch(0.0f),
    yaw(-90.0f),
    width(width),
    height(height),
    ratio((float) width / (float) height)
{}

Camera::~Camera() {};

void Camera::updateVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getMVP(const glm::vec3 &model)
{
    updateVectors();

    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), model);
    glm::mat4 mvp = projection * view * modelMatrix;
    return mvp;
}


void Camera::setFOV(float fov)
{
    assert(fov >= MIN_FOV && fov <= MAX_FOV);

    this->fov = fov;
}

void Camera::setClippingPlanes(float nearPlane, float farPlane)
{
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);

    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Camera::setDimensions(int width, int height)
{
    this->width = width;
    this->height = height;

    float ratio = (float) width / (float) height;
    assert(ratio > 0.0f);

    this->ratio = ratio;
}

void Camera::processKeyboard(Keys &keys, float deltaTime)
{
    float velocity = speed * deltaTime;
    
    if (keys[GLFW_KEY_W])
    {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_S])
    {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_A])
    {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        position += right * velocity;
    }
}

void Camera::processMouseMovement(Cursor const& cursor)
{
    float xoffset = (cursor.x2 - cursor.x1) * sensitivity;
    float yoffset = (cursor.y1 - cursor.y2) * sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > PITCH_LIMIT)
    {
        pitch = PITCH_LIMIT;
    }
    if (pitch < -PITCH_LIMIT)
    {
        pitch = -PITCH_LIMIT;
    }


    updateVectors();
}