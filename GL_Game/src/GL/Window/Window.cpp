//
//  Window.cpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#include "Window.h"


GLFWwindow* Engine::Window::main = nullptr;

int Engine::Window::WIDTH = 1024;
int Engine::Window::HEIGHT = 768;

glm::vec2 Engine::Window::mousePosition = glm::vec2(-90.0f, 0.0f);




void Engine::Window::setSize(int width, int height) {
    
    // TODO: Set by proportion size
    
    if (width < 1024 || height < 720) {
        std::cout << "[WINDOW] Error! Cannot set size less than 1024x720 pixels!" << std::endl;
        exit(0);
    }
    
    Engine::Window::WIDTH = width;
    Engine::Window::HEIGHT = height;
    
}





int Engine::Window::getWidth() {
    return Engine::Window::WIDTH;
}





int Engine::Window::getHeight() {
    return Engine::Window::HEIGHT;
}






GLFWwindow* Engine::Window::getInstance() {
    
    if (Engine::Window::main == nullptr) {
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint is specific for each platform (e.g. mac OS, windows 10...)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // If the version of the user's GPU are below of the GL requirements... We must handle
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, 0);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    #ifdef MAC_OS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Support to OpenGL on Mac OS due to the new API called Metal
    #endif

        std::cout << "Application started!" << std::endl;

        // Creating the window regardless the operating system
        Engine::Window::main = glfwCreateWindow(Engine::Window::WIDTH, Engine::Window::HEIGHT, "My Game", NULL, NULL);

        // Handling the error if the window wasn't created
        if (Engine::Window::main == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(Engine::Window::main);
        glfwSetFramebufferSizeCallback(Engine::Window::main, Engine::Window::framebufferSizeCallback); // Registering a callback related to Window resize
        glfwSetCursorPosCallback(Engine::Window::main, Engine::Window::mouseCallback);

        glfwSetInputMode(Engine::Window::main, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hiding the mouse's cursor
        glfwSetCursorPos(Engine::Window::main, Engine::Window::mousePosition.x, Engine::Window::mousePosition.y);

        // Loading GLAD's manager to handle OpenGL functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }
    }
    
    return Engine::Window::main;
}






void Engine::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Setting the viewport to a new size!
}






void Engine::Window::mouseCallback(GLFWwindow* window, double posX, double posY) {
    
    float offsetX = posX - Engine::Window::mousePosition.x;
    float offsetY = Engine::Window::mousePosition.y - posY;
    
    Engine::Window::mousePosition.x = posX;
    Engine::Window::mousePosition.y = posY;
    
    float sensitivity = 0.1f;
    
    offsetX *= sensitivity;
    offsetY *= sensitivity;
    
    Engine::Camera* camera = Engine::Camera::getInstance();
    glm::vec3 camRotation = camera->getRotation();
    
    camRotation.x = glm::mod(camRotation.x + offsetX, 360.0f);
    camRotation.y += offsetY;
    
    if (camRotation.y > 89.0f)
        camRotation.y = 89.0f;
    else if (camRotation.y < -89.0f)
        camRotation.y = -89.0f;
    
    camera->setRotation(camRotation);
    
}


