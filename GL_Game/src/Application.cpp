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
	char* shaderPath = (char*)SHADER_PATH;
	Engine::Shader shader = Engine::Shader::Shader(
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Vertex.vert",
		"C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\src\\GL\\Render\\Shaders\\Test_Fragment.frag");





	/* ------- LOADING TEXTURES DATA --------- */

	Engine::Texture2D* texture = new Engine::Texture2D("C:\\Users\\vinny\\Documents\\GitHub\\GL_Game\\GL_Game\\assets\\container.jpg", &shader);

	Engine::Entity* entity = new Engine::Entity(0.25, 0.25f, texture);

	Engine::Entity* entity2 = new Engine::Entity(-0.25, -0.25f, texture);






	/* --------- MAIN LOOP ------------ */
	while (!glfwWindowShouldClose(window)) {
        
		Engine::InputEvent::processInput(window);  // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT);		  // Painting the with the clearColor parameters


		entity->draw();
		entity2->draw();


		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}




	glfwTerminate();

	return 0;
}
