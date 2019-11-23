#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GL/Window/Window.h"
#include "GL/Render/Shader.h"
#include "Events/InputEvent.h"
#include <string>

#define SHADER_PATH "C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\"

int main() {

	glfwInit();

    GLFWwindow* window = Engine::Window::instantiate();

    unsigned int VBO;          // Vertex Buffer Object (Holds m vertices which can form a triangle)
	unsigned int VAO;          // Vertex Array Object (Holds n VBOs, which can be n triangles)

	float vertices[] = {
	 -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // left
     0.0f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  // top
     0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  // right
	};

	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};
    


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // Setting the S axis to be mirrored
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // Setting the R axis to be mirrored


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glGenVertexArrays(1, &VAO);     // Creating "two" Vertex Array Object
    glGenBuffers(1, &VBO);			// Creating "two" Vertex Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(VAO);													   // Signalizing to GPU that "VAO" must be used now
	glBindBuffer(GL_ARRAY_BUFFER, VBO);										   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data
    
    // TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Setting the first pointer to read parameters related to POSITION
    glEnableVertexAttribArray(0);                                                 // Saying which vertex attrib must be handled (which is ZERO)

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Setting the first pointer to read parameters related to POSITION
	glEnableVertexAttribArray(1);																	// Saying which vertex attrib must be handled (which is ONE)




	// Creating shader program
	char* shaderPath = (char*)SHADER_PATH;
	Engine::Shader shader = Engine::Shader::Shader(
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Vertex.vert",
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Fragment.frag");



	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);  // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT);		  // Painting the with the clearColor parameters


		glUseProgram(shader.id);

		glBindVertexArray(VAO);
        glad_glDrawArrays(GL_TRIANGLES, 0, 3);
        

		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}

	glfwTerminate();

	return 0;
}
