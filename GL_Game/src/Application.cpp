#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Tools/StringExtension.h"
#include "GL/Window/Window.h"
#include "GL/Render/Shader.h"
#include "Entities/Entity.h"
#include "Events/InputEvent.h"
#include "Textures/Texture2D.h"
#include "Camera/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef MAC_OS
    #define PROJECT_PATH "/Users/vinicius/Documents/GitHub/GL_Game/GL_Game"
#else
    #define PROJECT_PATH "C:/Users/vinny/Documents/GitHub/OpenGL-Simple-Renderer/GL_Game"
#endif


int main() {

	glfwInit();

	/* ------- PREPARING THE WINDOW, IT CONTEXT AND THE SHADER PROGRAM -------- */

	// Instantiating with the Window singleton a new GLFWwindow (regardless the O.S.)
    Engine::Window::setSize(1920, 1080);
    GLFWwindow* window = Engine::Window::getInstance();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);
    
	// Creating shader program
	glEnable(GL_DEPTH_TEST);

	char* vertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Test_Vertex.vert");
	char* fragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Test_Fragment.frag");

	Engine::Shader shader = Engine::Shader(vertexPath, fragPath);





	/* ------- LOADING TEXTURES DATA --------- */

	char* texturePath = StringExtension::join(PROJECT_PATH, "/assets/container.jpg");
	Engine::Texture2D* texture = new Engine::Texture2D(texturePath, &shader);

	glm::vec3 position;
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	Engine::Entity* entity1 = new Engine::Entity(position, texture);




    
    /* --------- MAIN LOOP ------------ */
    
	float previousTimeValue = 0.0f;
	float frameDeltaTime = 0.0f;

	Engine::Camera* mainCamera = Engine::Camera::getInstance();

	while (!glfwWindowShouldClose(window)) {
        
		frameDeltaTime = glfwGetTime() - previousTimeValue;
		previousTimeValue = glfwGetTime();

		Engine::InputEvent::processInput(window, frameDeltaTime);   // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					    // Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		    // Painting the with the clearColor parameters

		shader.enable();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Engine::Window::getWidth() / (float)Engine::Window::getHeight(), 0.1f, 100.0f);
		shader.setMat4Uniform("projection", projection);



		glm::vec3 position = mainCamera->getPosition();


		glm::mat4 view = glm::lookAt(
			position,									// Where the camera is in S (space)
			position + mainCamera->getFrontVector(),	// Desired point look into the space S
			mainCamera->getUpVector());					// Up Vector

		shader.setMat4Uniform("view", view);

		entity1->draw();




		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}




	glfwTerminate();

	return 0;
}
