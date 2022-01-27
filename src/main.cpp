#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <camera.h>
#include <shader.h>
#include <world.h>
#include <renderer.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int WINDOW_WIDTH  = 800;
int WINDOW_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int lastX = WINDOW_WIDTH / 2;
int lastY = WINDOW_HEIGHT / 2;

World world = World();
Camera camera(0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 45.0f);

bool mouseInit = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WINDOW_WIDTH  = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 5.0f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.transform.position += cameraSpeed * camera.transform.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.transform.position -= cameraSpeed * camera.transform.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.transform.position -= glm::normalize(glm::cross(camera.transform.front, camera.transform.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.transform.position += glm::normalize(glm::cross(camera.transform.front, camera.transform.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.transform.position += cameraSpeed * WORLD_UP;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.transform.position -= cameraSpeed * WORLD_UP;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(mouseInit){
        lastX = xpos;
        lastY = ypos;
        mouseInit = false;
    }
    
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 2.0f * deltaTime;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camera.transform.rotate(yOffset, xOffset, 0);

    if(camera.transform.rotation.x > 89.0f)
    camera.transform.setPitch(89.0f);
    if(camera.transform.rotation.x < -89.0f)
    camera.transform.setPitch(-89.0f);
}

int main(int, char**)
{
    stbi_set_flip_vertically_on_load(true);


    glfwInit();
    // Configuring glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating the window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft", NULL, NULL);

    if(window == NULL)
    {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the view port to the window size
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // On user change window size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Setting up the clear color
    glClearColor(.20f, .20f, .7f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

/*
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 11
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 12
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 13

        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 14

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 15
    };*/



    /*unsigned int indices[] = {  
        0, 1, 2, 2, 3, 0, // LEFT SIDE
        4, 5, 6, 6, 7, 4, // RIGHT SIDE
        8, 9, 10, 10, 4, 8, // BACK SIDE
        11, 2, 12, 12, 13, 11, // FRONT SIDE
        10, 14, 5, 5, 4, 10, // BOTTOM
        3, 2, 11, 11, 15, 3 // TOP
    };*/


    /*unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);


    int width, height, nbrChannel;
    //----- TEXTURE
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data = stbi_load("../res/textures/wood.png", &width, &height, &nbrChannel, 0);
    if(!data){
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    /*
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    data = stbi_load("../res/textures/emoji.png", &width, &height, &nbrChannel, 0);
    if(!data){
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    */

    //-------------

    Shader program("../res/shader.vert", "../res/shader.frag");

    program.use();
    program.setInt("uTexture", 0);
    // program.setInt("uTexture2", 1);


    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;

    world.chunks[0][0].generateMesh();

    world.chunks[0][1].generateMesh();

    world.chunks[0][2].generateMesh();

    // Rendering loop
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSetWindowTitle(window, std::to_string(1.0f / deltaTime).c_str());

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        view = glm::lookAt(camera.transform.position, camera.transform.position + camera.transform.front, camera.transform.up);
        projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        program.setMat4("projection", glm::value_ptr(projection));
        program.setMat4("view", glm::value_ptr(view));
        program.use();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);
        // glBindVertexArray(VAO);
        /*for(int i = 0; i < 32; i+=1)
        {
            for(int j = 0; j < 32; j+=1)
            {
                for(int k = 0; k < 32; k+=1){
                    model = glm::mat4(1.0f);
                    // model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    model = glm::translate(model, glm::vec3(i, -32+k, j));
                    // glm::vec3 offset(i, -64+k, j);
                    // model[3] = model[0] * offset[0] + model[1] * offset[1] + model[2] * offset[2] + model[3];
                    program.setMat4("model", glm::value_ptr(model));
                    // glDrawArrays(GL_TRIANGLES, 0, 36);
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                }
            }
        }*/

        chunk_renderer(world.chunks[0][0], program);
        chunk_renderer(world.chunks[0][1], program);
        chunk_renderer(world.chunks[0][2], program);

        //---------------------------------------------------------

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //---------------------------------------------------------



        // Event listener
        glfwPollEvents();

        // Drawing image
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
