//
//  Window.cpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#include "Window.h"


GLFWwindow* Engine::Window::instantiate() {
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
    GLFWwindow* window = glfwCreateWindow(1024, 768, "My Game", NULL, NULL);

    // Handling the error if the window wasn't created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    // Loading GLAD's manager to handle OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, 1024, 768);

    glfwSetFramebufferSizeCallback(window, Engine::Window::framebufferSizeCallback); // Registering a callback related to Window resize

    return window;
}

void Engine::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Setting the viewport to a new size!
}


