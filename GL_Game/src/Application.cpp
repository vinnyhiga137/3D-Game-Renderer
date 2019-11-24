#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "GL/Window/Window.h"
#include "GL/Render/Shader.h"
#include "Events/InputEvent.h"
#include "Textures/Texture2D.h"

#define SHADER_PATH "C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\"

int main() {

	glfwInit();

	// Instantiating with the Window factory a new GLFWwindow (regardless the O.S.)
    GLFWwindow* window = Engine::Window::instantiate();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);

	// Creating shader program
	char* shaderPath = (char*)SHADER_PATH;
	Engine::Shader shader = Engine::Shader::Shader(
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Vertex.vert",
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Fragment.frag");



    unsigned int VBO, EBO, VAO;          

	float verticesData[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right (0)
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right (1)
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left (2)
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left (3)
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);     // Creating "one" Vertex Array Object
	glGenBuffers(1, &EBO);			// Creating "one" Element Buffer Object
    glGenBuffers(1, &VBO);			// Creating "one" Vertex Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(VAO);															   // Signalizing to GPU that "VAO" must be used now
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data
    
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										   // Signalizing to GPU that "EBO" must be used now
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   // Sending to the memory buffer the EBO's data

    // TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Setting the first pointer to read parameters related to POSITION
    glEnableVertexAttribArray(0);                                                 // Saying which vertex attrib must be handled (which is ZERO)

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Setting the first pointer to read parameters related to POSITION
	glEnableVertexAttribArray(1);																	// Saying which vertex attrib must be handled (which is ONE)

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	/* ------------------------------------------------------- */

	stbi_set_flip_vertically_on_load(true);

	Engine::Texture2D* texture1 = new Engine::Texture2D("C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\assets\\container.jpg");
	Engine::Texture2D* texture2 = new Engine::Texture2D("C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\assets\\awesomeface.png", GL_RGBA);

	shader.enable();
	glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0); // set it manually
	shader.setIntUniform("texture2", 1); // or with shader class

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);  // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT);		  // Painting the with the clearColor parameters

		glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture1->data);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->data);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}

	glfwTerminate();

	return 0;
}
