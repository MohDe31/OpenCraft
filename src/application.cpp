#include <application.h>

#include <iostream>

#include <camera.h>
#include <renderer.h>
#include <shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Application::WINDOW_WIDTH  = width;
    Application::WINDOW_HEIGHT = height;
    glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(Application::mouseInit){
        Application::lastX = xpos;
        Application::lastY = ypos;
        Application::mouseInit = false;
    }
    
    float xOffset = xpos - Application::lastX;
    float yOffset = Application::lastY - ypos; 

    Application::lastX = xpos;
    Application::lastY = ypos;

    const float sensitivity = 2.0f * Application::deltaTime;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    Application::camera.transform.rotate(yOffset, xOffset, 0);

    if(Application::camera.transform.rotation.x > 89.0f)
    Application::camera.transform.setPitch(89.0f);
    if(Application::camera.transform.rotation.x < -89.0f)
    Application::camera.transform.setPitch(-89.0f);

    /*std::cout << Application::camera.transform.rotation.x << " " <<
                 Application::camera.transform.rotation.y << " " <<
                 Application::camera.transform.rotation.z << std::endl;*/
}

void Application::ProcessInput(GLFWwindow *window)
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
void Application::Init(){
    glfwInit();
    
    // Configure glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Creating the window
    Application::window = glfwCreateWindow(Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT, "OpenCraft", NULL, NULL);

    if(Application::window == NULL)
    {
        std::cout << "APPLICATION::INIT::Failed to create a window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(Application::window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "APPLICATION::INIT::Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT);

    glfwSetFramebufferSizeCallback(Application::window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(Application::window, MouseCallback);

    glClearColor(.20f, .20f, .7f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(Application::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // TODO: Remove this bit;
    int width, height, nbrChannel;
    //----- TEXTURE
    glGenTextures(1, &(Application::texture));
    glBindTexture(GL_TEXTURE_2D, Application::texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data = stbi_load("../res/textures/dirt.png", &width, &height, &nbrChannel, 0);
    if(!data){
        std::cout << "Failed to load texture" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    Application::program = Shader("../res/shader.vert", "../res/shader.frag");
    Application::program.use();
    Application::program.setInt("uTexture", 0);

    std::cout << "HELLO" << std::endl;
    Application::world = World();

    Application::world.chunks[0][0].generateMesh();
    Application::world.chunks[0][1].generateMesh();
    Application::world.chunks[0][2].generateMesh();
    Application::world.chunks[1][0].generateMesh();
    Application::world.chunks[1][1].generateMesh();
    Application::world.chunks[1][2].generateMesh();
    Application::world.chunks[2][0].generateMesh();
    Application::world.chunks[2][1].generateMesh();
    Application::world.chunks[2][2].generateMesh();
}


void Application::Run(){

    while(!glfwWindowShouldClose(Application::window))
    {
        float currentFrame = glfwGetTime();
        Application::deltaTime = currentFrame - Application::lastFrame;
        Application::lastFrame = currentFrame;

        glfwSetWindowTitle(window, std::to_string(1.0f / deltaTime).c_str());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Application::ProcessInput(Application::window);

        Application::view = glm::lookAt(Application::camera.transform.position, Application::camera.transform.position + Application::camera.transform.front, Application::camera.transform.up);
        Application::projection = glm::perspective(glm::radians(45.0f), (float) Application::WINDOW_WIDTH / Application::WINDOW_HEIGHT, 0.1f, 100.0f);

        Application::program.setMat4("projection", glm::value_ptr(Application::projection));
        Application::program.setMat4("view", glm::value_ptr(Application::view));

        
        Application::program.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Application::texture);
        

        chunk_renderer(Application::world.chunks[0][0], Application::program);
        chunk_renderer(Application::world.chunks[0][1], Application::program);
        chunk_renderer(Application::world.chunks[0][2], Application::program);
        chunk_renderer(Application::world.chunks[1][0], Application::program);
        chunk_renderer(Application::world.chunks[1][1], Application::program);
        chunk_renderer(Application::world.chunks[1][2], Application::program);
        chunk_renderer(Application::world.chunks[2][0], Application::program);
        chunk_renderer(Application::world.chunks[2][1], Application::program);
        chunk_renderer(Application::world.chunks[2][2], Application::program);

        glfwPollEvents();

        glfwSwapBuffers(Application::window);
    }

    glfwTerminate();
}