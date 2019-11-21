//
//  InputEvent.cpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#include "InputEvent.h"

void Engine::InputEvent::processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

