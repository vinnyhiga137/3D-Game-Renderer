#pragma once

#include <glad/glad.h>

#include "../GL/MemoryManagement.h"
#include "../Materials/Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine {

	class Entity {
	private:
        
        // Attributes
		unsigned int VAO;
		Material* material;
		glm::vec3 position;
        
	public:
        
        /// <summary>
        /// Constructor for instantiating an Entity.
        ///
        /// PARAMETERS:
        /// - position: 3D vector related for the position
        /// - texture: 2D texture object
        ///
        /// </summary>
		Entity(glm::vec3 position, Material* material);

        glm::vec3 getPosition();

        /// <summary>
        /// This methods draws the object into the screen.
        ///
        /// This method must be called each frame / tick, because it will calculate the internal matrices and
        /// after the "projection" and "view" matrix calculations on somewhere on the main loop, so it will
        /// allow the entity be rotated or moved.
        /// </summary>
		void draw();
	};

}
