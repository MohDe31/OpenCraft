#pragma once
#include <transform.h>

class Camera{

    public:
        float fov;

        Transform transform;

        Camera(float xpos, float ypos, float zpos,
               float pitch, float yaw, float roll,
               float _fov);
};