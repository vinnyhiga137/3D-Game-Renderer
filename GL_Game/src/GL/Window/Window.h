//
//  Window.hpp
//  GL_Game
//
//  Created by Vinicius Hiroshi Higa on 21/11/19.
//  Copyright © 2019 Vinicius Higa. All rights reserved.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

    class Window {
        
    public:
        Window();
        ~Window();

        static GLFWwindow* instantiate();
        
        /// <summary>
        /// Function for handling events when the window is resized.
        ///
        /// PARAMETERS:
        /// - window: Pointer to the window to be handled
        /// - width: Window's new width
        /// - height: Window's new height
        ///
        /// </summary>
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    };

}
