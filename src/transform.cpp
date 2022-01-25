#include <transform.h>

Transform::Transform(){}

Transform::Transform(float xpos, float ypos, float zpos, float pitch, float yaw, float roll)
{
    position = glm::vec3(xpos, ypos, zpos);
    rotation = glm::vec3(pitch, yaw, roll);
}

void Transform::setRotation(float pitch, float yaw, float roll)
{
    rotation.x = pitch;
    rotation.y = yaw;
    rotation.z = roll;

    updateVectors();
}

void Transform::setPitch(float value)
{
    rotation.x = value;
    updateVectors();
}

void Transform::setYaw(float value)
{
    rotation.y = value;
    updateVectors();
}

void Transform::setRoll(float value)
{
    rotation.z = value;
    updateVectors();
}

void Transform::rotate(float pitch, float yaw, float roll)
{
    rotation.x += pitch;
    rotation.y += yaw;
    rotation.z += roll;

    updateVectors();
}

void Transform::updateVectors()
{
    front = glm::vec3(
        cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
        sin(glm::radians(rotation.x)),
        sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
    );

    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, WORLD_UP));
    up    = glm::normalize(glm::cross(right, front));
}