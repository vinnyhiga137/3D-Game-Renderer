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

	// Instantiating with the Window singleton a new GLFWwindow (regardless the O.S.)
    Engine::Window::setSize(1366, 768);
    GLFWwindow* window = Engine::Window::getInstance();

	// Signalizing the image loader that we need to flip vertically the image before inserting into the shader program
	stbi_set_flip_vertically_on_load(true);
    







	// Creating the box(es)
	glEnable(GL_DEPTH_TEST);
    Engine::Shader::initialSetup(PROJECT_PATH);

    // Setting up the material's properties
    Engine::Color colorParams;
    colorParams.shininess = 64;

    // Setting up how to handle the light in the material...
    Engine::Light lightParams;
    lightParams.ambientLightStrength = glm::vec3(0.2f, 0.2f, 0.2f);
    lightParams.diffuseLightStrength = glm::vec3(0.5f, 0.5f, 0.5f);
    lightParams.specularLightStrength = glm::vec3(1.0f, 1.0f, 1.0f);
    lightParams.lightPosition = glm::vec3(0.f, 0.f, 0.f); // The Position is fixed due to the Light Emitter obj isn't instantiated yet!

    Engine::Texture2D* texture = new Engine::Texture2D(StringExtension::join(PROJECT_PATH, "/assets/container2.png"));
    Engine::Texture2D* complTexture = new Engine::Texture2D(StringExtension::join(PROJECT_PATH, "/assets/container2_specular.png"));

    Engine::Material* material = new Engine::Material("Box", colorParams, lightParams, "Debug", texture, complTexture);
    Engine::Material::materialList[0] = material;
    

    Engine::Entity* entity1 = new Engine::Entity(glm::vec3(0.f, 0.f, 0.f));
    Engine::Entity* entity2 = new Engine::Entity(glm::vec3(1.f, 0.f, -1.f));
    Engine::Entity* entity3 = new Engine::Entity(glm::vec3(0.f, 0.f, -1.f));
    Engine::Entity* entity4 = new Engine::Entity(glm::vec3(0.f, 1.f, -1.f));






    /* --------------- DEBUG ------------- */
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



        // TODO: Optimize the lamp position call...
        // Drawing the boxes
        entity1->draw(lamp->getPosition());    // Updating the Local Matrix + Texture
        entity2->draw(lamp->getPosition());
        entity3->draw(lamp->getPosition());
        entity4->draw(lamp->getPosition());



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
