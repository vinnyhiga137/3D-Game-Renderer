#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

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
    Engine::Window::setSize(1920, 1080);
    GLFWwindow* window = Engine::Window::getInstance();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);
    







	// Creating shader program
	glEnable(GL_DEPTH_TEST);
    Engine::Shader::initialSetup(PROJECT_PATH);

    Engine::Color colorParams;
    colorParams.ambientStrength = glm::vec3(85.f / 255.f, 255.f / 255.f, 59.f / 255.f);
    colorParams.diffuseStrength = glm::vec3(85.f / 255.f, 255.f / 255.f, 59.f / 255.f);
    colorParams.specularStrength = glm::vec3(0.5f, 0.5f, 0.5f);
    colorParams.shininess = 32;

    Engine::Light lightParams;
    lightParams.ambientLightStrength = glm::vec3(0.2f, 0.2f, 0.2f);
    lightParams.diffuseLightStrength = glm::vec3(0.5f, 0.5f, 0.5f);
    lightParams.specularLightStrength = glm::vec3(1.0f, 1.0f, 1.0f);
    lightParams.lightPosition = glm::vec3(0.f, 0.f, 0.f); // The Position is fixed due to the Light Emitter obj isn't instantiated yet!

    Engine::Material* material = new Engine::Material("Box", colorParams, lightParams, "Debug");
    Engine::Material::materialList[0] = material;
    

    Engine::Entity* entity1 = new Engine::Entity(glm::vec3(0.f, 0.f, 0.f));
    Engine::Entity* entity2 = new Engine::Entity(glm::vec3(1.f, 0.f, -1.f));
    Engine::Entity* entity3 = new Engine::Entity(glm::vec3(0.f, 0.f, -1.f));
    Engine::Entity* entity4 = new Engine::Entity(glm::vec3(0.f, 1.f, -1.f));







	char* lampVertexPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Vertex.vert");
	char* lampFragPath = StringExtension::join(PROJECT_PATH, "/src/GL/Render/Shaders/Lamp_Fragment.frag");

	Engine::Shader lampShader = Engine::Shader("Light", lampVertexPath, lampFragPath);
	Engine::Debug::Lamp* lamp = new Engine::Debug::Lamp(glm::vec3(1.f, 0.f, -1.f), &lampShader);





    
    /* --------- MAIN LOOP ------------ */
    
	float previousTimeValue = 0.0f;
	float frameDeltaTime = 0.0f;

	while (!glfwWindowShouldClose(window)) {
        
		frameDeltaTime = glfwGetTime() - previousTimeValue;
		previousTimeValue = glfwGetTime();

		Engine::InputEvent::processInput(window, frameDeltaTime);   // Checking for interruptions

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);

        glClearColor((float) 12.0f / 255.0f, (float) 86.0f / 255.0f, (float) 232.0f / 255.0f, 1.0f);	// Setting the desired color on the background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		                                        // Painting the with the clearColor parameters



        // Drawing the boxes
        entity1->getMaterial()->getShaderProgram()->updateDynamicData();
        entity1->getMaterial()->updateLightData(lamp->getPosition());
        
        entity1->draw();
        entity2->draw();
        entity3->draw();
        entity4->draw();



		// Drawing the lamp
        lamp->getShaderProgram()->updateLightEmitterData();
		lamp->setPosition(glm::vec3(glm::sin(glfwGetTime()) * 3.f, 0.f, glm::cos(glfwGetTime()) * 3.f));
		lamp->draw();




		glfwSwapBuffers(window); // Signalize the GPU to render another "frame" into the screen
		glfwPollEvents();		 // Signalize tha application that an event was dispatched
	}
	



	glfwTerminate();

	return 0;
}
