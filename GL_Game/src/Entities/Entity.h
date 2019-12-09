#pragma once

#include <glad/glad.h>

#include "../GL/MemoryManagement.h"
#include "../Math/Vector2D.h"
#include "../Textures/Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine {

	class Entity {
	private:
		unsigned int VAO;
		Texture2D* texture;
		Vector2 position;
	public:
		Entity(Vector2 position, Texture2D* texture);

		void draw();
	};

}