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
		Entity(float x, float y, float z, Texture2D* texture);

		void draw();
	};

}