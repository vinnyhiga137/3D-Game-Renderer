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

    
    unsigned int VBO; // Vertex Buffer Object (Holds m vertices which can form a triangle)
	unsigned int VAO; // Vertex Array Object (Holds n VBOs, which can be n triangles)
	unsigned int EBO; // Elements Buffer Object (Holds m vertices which can form a triangle OR quad...)

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f, // Vertex 1
	//	 0.5f, -0.5f, 0.0f, // Vertex 2
	//	 0.0f,  0.5f, 0.0f  // Vertex 3
	//};

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // The index always will start from ZERO
		0, 1, 3,				// First triangle
		1, 2, 3					// Second triangle
	};

	glGenVertexArrays(1, &VAO); // Creating "one" Vertex Array Object
    glGenBuffers(1, &VBO);		// Creating "one" Vertex Buffer Object
	glGenBuffers(1, &EBO);		// Creating "one" Elements Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(VAO);													   // Signalizing to GPU that "VAO" must be used now
	glBindBuffer(GL_ARRAY_BUFFER, VBO);										   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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


	// TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Setting the first pointer read parameters
	glEnableVertexAttribArray(0);												  // Saying which vertex attrib must be handled (which is ZERO)

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);  // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT);		  // Painting the with the clearColor parameters

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Optional?
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();

	return 0;
}
