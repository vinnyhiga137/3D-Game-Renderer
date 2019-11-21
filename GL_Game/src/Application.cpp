#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GL/Window.h"
#include "Events/InputEvent.h"

int main() {

	glfwInit();

    GLFWwindow* window = Engine::Window::instantiate();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    unsigned int VBO;
    glGenBuffers(1, &VBO); // Creating ID for the VBO (Object)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data
    
	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT); // Painting the with the clearColor parameters

        Engine::InputEvent::processInput(window);  // Checking for interruptions
        
		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents(); // Signalize tha application that an event was dispatched
	}

	glfwTerminate();

	return 0;
}
