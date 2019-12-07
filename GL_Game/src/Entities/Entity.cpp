#include "Entity.h"
#include <GLFW\glfw3.h>

Engine::Entity::Entity(float x, float y, float z, Texture2D* texture) {

	Vector2 position;
	position.x = x;
	position.y = y;
	position.z = z;

	this->position = position;

	this->texture = texture;


	float verticesData[] = {
		 // 3D Position		  // 2D Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indexes[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	Engine::MemoryManagement::generateGeometryData(verticesData, sizeof(verticesData), indexes, sizeof(indexes), &(this->VAO));

}






/// <summary>
/// This methods draws the object into the screen.
///
/// This method must be called each frame / tick, because it will calculate the internal matrices
/// to allow the texture / entity be rotated or moved.
/// </summary>
void Engine::Entity::draw() {

	glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, this->texture->data);
	glUniform1i(glGetUniformLocation(this->texture->shader->id, "uTexture"), 0); // Setting the texture into the Uniform variable

	this->texture->shader->enable();

	// Updating the VAO (Vertex Array Object) 
	glBindVertexArray(this->VAO);

	////////////////////////////////////////////////////////////////////
	// The next steps we need to the deal with the following equation //
	//																  //
	// Vclip=Mprojection⋅Mview⋅Mmodel⋅Vlocal							  //
	////////////////////////////////////////////////////////////////////


	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, this->position.z));
	//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Sending into the shader the updated model matrix
	this->texture->shader->setMat4Uniform("model", model);


	glDrawArrays(GL_TRIANGLES, 0, 36);

}
