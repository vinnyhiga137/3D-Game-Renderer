#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GL/Window.h"
#include "GL/Shaders/ShaderHandler.h"
#include "Events/InputEvent.h"
#include <string>


int main() {

	glfwInit();

    GLFWwindow* window = Engine::Window::instantiate();

//    int nrAttributes;
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    unsigned int VBO[2];          // Vertex Buffer Object (Holds m vertices which can form a triangle)
	unsigned int VAO[2];          // Vertex Array Object (Holds n VBOs, which can be n triangles)

	float vertices[] = {
	 -0.9f, -0.5f, 0.0f,  // left
     -0.0f, -0.5f, 0.0f,  // right
     -0.45f, 0.5f, 0.0f,  // top
	};
    
    float vertices2[] = {
     0.0f, -0.5f, 0.0f,  // left
     0.9f, -0.5f, 0.0f,  // right
     0.45f, 0.5f, 0.0f   // top
    };


	glGenVertexArrays(2, VAO);     // Creating "two" Vertex Array Object
    glGenBuffers(2, VBO);		// Creating "two" Vertex Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(VAO[0]);													   // Signalizing to GPU that "VAO" must be used now
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);										   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data
    
    // TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Setting the first pointer read parameters
    glEnableVertexAttribArray(0);                                                  // Saying which vertex attrib must be handled (which is ZERO)
    
    
    glBindVertexArray(VAO[1]);                                                       // Signalizing to GPU that "VAO" must be used now
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);                                           // Signalizing to GPU that "VBO" must be used now
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data

    // TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Setting the first pointer read parameters
    glEnableVertexAttribArray(0);                                                  // Saying which vertex attrib must be handled (which is ZERO)

	// VERTEX SHADER RELATED CODE
	const char* vertexShaderCode =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";

	// FRAGMENT SHADER RELATED CODE
	const char* fragmentShaderCode =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main() {\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";



	// Compiling shaders
	unsigned int vertexShader = Engine::ShaderHandler::createShaderAndCompile(GL_VERTEX_SHADER, vertexShaderCode);
	unsigned int fragmentShader = Engine::ShaderHandler::createShaderAndCompile(GL_FRAGMENT_SHADER, fragmentShaderCode);

	if (vertexShader == 0 || fragmentShader == 0) {
		std::cout << "Shaders were not compiled successfully!" << std::endl;
		return -1;
	}


	// Creating shader program
	unsigned int shaderProgram = Engine::ShaderHandler::createShaderProgram(&vertexShader, &fragmentShader);

	if (shaderProgram == 0) {
		std::cout << "Shader program failed to be created!" << std::endl;
		return -1;
	}

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);  // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT);		  // Painting the with the clearColor parameters

		glUseProgram(shaderProgram);
        
		glBindVertexArray(VAO[0]);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(VAO[1]);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();

	return 0;
}
