#pragma once

#include <iostream>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace Engine {

	// Singleton class
	class Camera {
	private:
		Camera();

		static Camera* main;

		glm::vec3 position;
        glm::vec3 rotation;
        
        glm::vec3 frontVector;

	public:

		glm::vec3 getPosition();
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec3 position);
        
        glm::vec3 getRotation();
        void setRotation(float x, float y, float z);
        void setRotation(glm::vec3 rotation);
        
		glm::vec3 getFrontVector();
		glm::vec3 getUpVector();

		static Camera* getInstance() {

			if (main == nullptr) {
				main = new Camera();
			}

			return main;

		};

	};

}
