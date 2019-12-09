//
//  InputEvent.hpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "../Camera/Camera.h"

namespace Engine {
    class InputEvent {
    public:
        /// <summary>
        /// Function for handling events when the window received an input.
        ///
        /// PARAMETERS:
        /// - window: Pointer to the window to be handled
        ///
        /// </summary>
        static void processInput(GLFWwindow* window, float deltaTime);

    private:
        static void moveCamera(GLFWwindow* window, float deltaTime);
    };
}
