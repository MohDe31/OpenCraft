#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <world.h>
#include <camera.h>
#include <shader.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


namespace Application {
    inline GLFWwindow* window = NULL;

    inline int WINDOW_WIDTH  = 800;
    inline int WINDOW_HEIGHT = 600;

    inline float deltaTime = 0.0f;
    inline float lastFrame = 0.0f;

    inline int lastX = WINDOW_WIDTH / 2;
    inline int lastY = WINDOW_HEIGHT / 2;

    inline World world;
    inline Camera camera(0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 45.0f);
    inline Shader program;//("/home/jae/Projects/CPP/OGL_ENGINE/res/shader.vert", "/home/jae/Projects/CPP/OGL_ENGINE/res/shader.frag");

    inline glm::mat4 projection;
    inline glm::mat4 view;

    inline unsigned int texture;

    inline bool mouseInit = false;

    void Init();
    void Run();

    void ProcessInput(GLFWwindow *window);

};