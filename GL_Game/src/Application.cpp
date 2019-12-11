#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Tools/StringExtension.h"
#include "GL/Window/Window.h"
#include "GL/Render/Shader.h"
#include "Entities/Entity.h"
#include "Entities/Debug/Lamp.h"
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

	/* ------- PREPARING THE WINDOW (IT CONTEXT) -------- */

	// Instantiating with the Window singleton a new GLFWwindow (regardless the O.S.)
    Engine::Window::setSize(1024, 768);
    GLFWwindow* window = Engine::Window::getInstance();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);
    






	/* ------- LOADING TEXTURES DATA --------- */

	// Creating shader program
	glEnable(GL_DEPTH_TEST);

	//char* vertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Test_Vertex.vert");
	//char* fragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Test_Fragment.frag");
	char* vertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Debug_Vertex.vert");
	char* fragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Debug_Fragment.frag");

	Engine::Shader shader = Engine::Shader(vertexPath, fragPath);


	char* texturePath = StringExtension::join(PROJECT_PATH, "/assets/container.jpg");
	//Engine::Texture2D* texture = new Engine::Texture2D(texturePath, &shader);
	Engine::Texture2D* texture = new Engine::Texture2D(&shader);

	glm::vec3 position;
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	Engine::Entity* entity1 = new Engine::Entity(position, texture);

	shader.setFloatUniform("ambientLightStrength", 0.25f);







	char* lampVertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Vertex.vert");
	char* lampFragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Fragment.frag");

	Engine::Shader lampShader = Engine::Shader(lampVertexPath, lampFragPath);


	Engine::Texture2D* lampTexture = new Engine::Texture2D(&lampShader); // This is a fake "texture", because will be used for debugging the "light"

	glm::vec3 lampPosition;
	lampPosition.x = 1.0f;
	lampPosition.y = 0.0f;
	lampPosition.z = -1.0f;

	Engine::Debug::Lamp* lamp = new Engine::Debug::Lamp(lampPosition, lampTexture);





    
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

        //glClearColor((float) 50.0f / 255.0f, (float) 84.0f / 255.0f, (float) 255.0f / 255.0f, 1.0f);	// Setting the desired color on the background
        glClearColor(0.f, 0.f, 0.f, 1.0f);                                                              // DEBUG: Black background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		                                        // Painting the with the clearColor parameters



		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
			(float)Engine::Window::getWidth() / (float)Engine::Window::getHeight(),
			0.1f, 100.0f);

		glm::vec3 position = mainCamera->getPosition();


		// Drawing the boxes
		shader.enable();
		shader.setMat4Uniform("projection", projection);

		glm::mat4 view = glm::lookAt(
			position,									
			position + mainCamera->getFrontVector(),	
			mainCamera->getUpVector());					

		shader.setMat4Uniform("view", view);
		entity1->draw();

		shader.setVec3Uniform("objectColor", 1.0f, 0.5f, 0.31f);
		shader.setVec3Uniform("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setVec3Uniform("lightPos", lamp->getPosition());



		// Drawing the lamp
		lampShader.enable();
		lampShader.setMat4Uniform("projection", projection);
		lampShader.setMat4Uniform("view", view);
		lamp->setPosition(glm::vec3(glm::sin(glfwGetTime()) * 3.f, 0.f, glm::cos(glfwGetTime()) * 3.f));
		lamp->draw();




		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}
	



	glfwTerminate();

	return 0;
}
