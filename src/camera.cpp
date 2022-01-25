#include <camera.h>
#include <transform.h>


Camera::Camera(float xpos, float ypos, float zpos,
               float pitch, float yaw, float roll,
               float _fov): transform(Transform(xpos, ypos, zpos, pitch, yaw, roll)), fov(_fov) {}