#pragma once

#include <glm/vec3.hpp>

namespace Engine {

	// Singleton class
	class Camera {
	private:
		Camera();

		static Camera* main;

		glm::vec3 position;

	public:

		glm::vec3* getPosition();
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