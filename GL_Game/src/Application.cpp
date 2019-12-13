#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Tools/StringExtension.h"
#include "GL/Window/Window.h"
#include "Entities/Entity.h"
#include "Entities/Debug/Lamp.h"
#include "Materials/Material.h"
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
    Engine::Window::setSize(1600, 900);
    GLFWwindow* window = Engine::Window::getInstance();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);
    






	/* ------- LOADING TEXTURES DATA --------- */

	// Creating shader program
	glEnable(GL_DEPTH_TEST);

	
	char* vertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Debug_Vertex.vert");
	char* fragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Debug_Fragment.frag");

	Engine::Shader shader = Engine::Shader(vertexPath, fragPath);

	Engine::Color colorParams;
	colorParams.ambientStrength = glm::vec3(1.0f, 0.5f, 0.31f);
	colorParams.diffuseStrength = glm::vec3(1.0f, 0.5f, 0.31f);
	colorParams.specularStrength = glm::vec3(0.5f, 0.5f, 0.5f);
	colorParams.shininess = 32;

	Engine::Light lightParams;
	lightParams.ambientLightStrength = glm::vec3(0.2f, 0.2f, 0.2f);
	lightParams.diffuseLightStrength = glm::vec3(0.5f, 0.5f, 0.5f);
	lightParams.specularLightStrength = glm::vec3(1.0f, 1.0f, 1.0f);
	lightParams.lightPosition = glm::vec3(0.f, 0.f, 0.f); // The Position is fixed due to the Light Emitter obj isn't instantiated yet!

	Engine::Material* material = new Engine::Material(colorParams, lightParams, &shader);

	Engine::Entity* entity1 = new Engine::Entity(glm::vec3(0.f, 0.f, 0.f), material);
    Engine::Entity* entity2 = new Engine::Entity(glm::vec3(1.f, 0.f, -1.f), material);
    Engine::Entity* entity3 = new Engine::Entity(glm::vec3(0.f, 0.f, -1.f), material);
    Engine::Entity* entity4 = new Engine::Entity(glm::vec3(0.f, 1.f, -1.f), material);







	char* lampVertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Vertex.vert");
	char* lampFragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Fragment.frag");

	Engine::Shader lampShader = Engine::Shader(lampVertexPath, lampFragPath);
	Engine::Debug::Lamp* lamp = new Engine::Debug::Lamp(glm::vec3(1.f, 0.f, -1.f), &lampShader);





    
    /* --------- MAIN LOOP ------------ */
    
	float previousTimeValue = 0.0f;
	float frameDeltaTime = 0.0f;

	Engine::Camera* mainCamera = Engine::Camera::getInstance();

	while (!glfwWindowShouldClose(window)) {
        
		frameDeltaTime = glfwGetTime() - previousTimeValue;
		previousTimeValue = glfwGetTime();

		Engine::InputEvent::processInput(window, frameDeltaTime);   // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);

        glClearColor((float) 0.0f / 255.0f, (float) 0.0f / 255.0f, (float) 40.0f / 255.0f, 1.0f);	// Setting the desired color on the background                                                          // DEBUG: Black background color
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
		material->updateLightData(lamp->getPosition());
		shader.setVec3Uniform("viewPos", mainCamera->getPosition());

		entity1->draw();
        entity2->draw();
        entity3->draw();
        entity4->draw();



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
