#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "GL/Window/Window.h"
#include "Entities/Entity.h"
#include "GL/Render/Shader.h"
#include "Events/InputEvent.h"
#include "Textures/Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SHADER_PATH "C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\"

int main() {

	glfwInit();

	/* ------- PREPARING THE WINDOW, IT CONTEXT AND THE SHADER PROGRAM -------- */

	// Instantiating with the Window factory a new GLFWwindow (regardless the O.S.)
    GLFWwindow* window = Engine::Window::instantiate();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);


	// Creating shader program
	glEnable(GL_DEPTH_TEST);

	char* shaderPath = (char*)SHADER_PATH;
	Engine::Shader shader = Engine::Shader::Shader(
		"C:\\Users\\vinny\\Documents\\GitHub\\OpenGL-Simple-Renderer\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Vertex.vert",
		"C:\\Users\\vinny\\Documents\\GitHub\\OpenGL-Simple-Renderer\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Fragment.frag");





	/* ------- LOADING TEXTURES DATA --------- */

	Engine::Texture2D* texture = new Engine::Texture2D("C:\\Users\\vinny\\Documents\\GitHub\\OpenGL-Simple-Renderer\\GL_Game\\assets\\container.jpg", &shader);

	Engine::Entity* entity1 = new Engine::Entity(0.0, 0.0f, 0.0f, texture);


	shader.enable();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1024.0f / (float)768.0f, 0.1f, 100.0f);
	shader.setMat4Uniform("projection", projection);


	/* --------- MAIN LOOP ------------ */
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);				// Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);					// Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Painting the with the clearColor parameters


		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		glm::mat4 view = glm::mat4(1.0f);

		view = glm::lookAt(
			glm::vec3(camX, 0.0, camZ), // Where the camera is in S (space)
			glm::vec3(0.0, 0.0, 0.0),	// Desired point look into the space S
			glm::vec3(0.0, 1.0, 0.0));  // Up Vector

		shader.setMat4Uniform("view", view);

		entity1->draw();




		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}




	glfwTerminate();

	return 0;
}
