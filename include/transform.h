#pragma once
#include <glm/glm/glm.hpp>

const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class Transform {

    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;

        Transform();
        Transform(float xpos, float ypos, float zpos, float pitch, float yaw, float roll);
        
        void setRotation(float pitch, float yaw, float roll);

        void setPitch(float value);
        void setYaw(float value);
        void setRoll(float value);

        void rotate(float pitch, float yaw, float roll);

    private:
        void updateVectors();
};