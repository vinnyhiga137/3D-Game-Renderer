//
//  InputEvent.cpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#include "InputEvent.h"

void Engine::InputEvent::processInput(GLFWwindow* window, float deltaTime) {

    // Checking if the application must stop / close
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Engine::InputEvent::moveCamera(window, deltaTime);
}





void Engine::InputEvent::moveCamera(GLFWwindow* window, float deltaTime) {

    float cameraSpeed = 3.0f * deltaTime;

    Engine::Camera* camera = Engine::Camera::getInstance();
    glm::vec3* cameraPosition = camera->getPosition();

    // Moving Forward...
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        *cameraPosition += cameraSpeed * camera->getFrontVector();
    }

    // Moving Backward...
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        *cameraPosition -= cameraSpeed * camera->getFrontVector();
    }

    // Moving to Right...
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        *cameraPosition += cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    // Moving to Left...
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        *cameraPosition += cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
    }

}
