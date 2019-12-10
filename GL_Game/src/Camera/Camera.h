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

        // Attributes
		static Camera* main;

		glm::vec3 position;
        glm::vec3 rotation;
        
        glm::vec3 frontVector;

	public:

        /// <summary>
        /// Method that gets a Vector 3D position of the camera
        ///
        /// </summary>
		glm::vec3 getPosition();
        
        /// <summary>
        /// Method that sets a new position for the camera
        ///
        /// PARAMETERS:
        /// - x: X axis position
        /// - y: Y axis position
        /// - z: Z axis position
        ///
        /// </summary>
        void setPosition(float x, float y, float z);
        
        /// <summary>
        /// Method that sets a new position for the camera
        ///
        /// PARAMETERS:
        /// - position: Vector 3D as new position
        ///
        /// </summary>
        void setPosition(glm::vec3 position);
        
        /// <summary>
        /// Method that gets a Vector 3D rotation of the camera
        ///
        /// </summary>
        glm::vec3 getRotation();
        
        /// <summary>
        /// Method that sets a new rotation for the camera
        ///
        /// PARAMETERS:
        /// - x: X axis position
        /// - y: Y axis position
        /// - z: Z axis position
        ///
        /// </summary>
        void setRotation(float x, float y, float z);
        
        /// <summary>
        /// Method that sets a new rotation for the camera
        ///
        /// PARAMETERS:
        /// - position: Vector 3D as new position
        ///
        /// </summary>
        void setRotation(glm::vec3 rotation);
        
        /// <summary>
        /// Method that gets the front vector
        ///
        /// </summary>
		glm::vec3 getFrontVector();
        
        /// <summary>
        /// Method that gets the up vector
        ///
        /// </summary>
		glm::vec3 getUpVector();

        /// <summary>
        /// Method that gets the singleton instance
        ///
        /// </summary>
		static Camera* getInstance() {

			if (main == nullptr) {
				main = new Camera();
			}

			return main;

		};

	};

}
