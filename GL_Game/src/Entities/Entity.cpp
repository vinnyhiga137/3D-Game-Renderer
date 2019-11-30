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



	////////////////////////////////////////////////////////////////////
	// The next steps we need to the deal with the following equation //
	//																  //
	// Vclip=Mprojection⋅Mview⋅Mmodel⋅Vlocal							  //
	////////////////////////////////////////////////////////////////////


	// Multiplying the X axis to rotate by -55 degrees into the [1, 0, 0] vector
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	// Translating the scene in the reverse direction of Z (we're dealing with a Z+ case)
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(this->position.x, this->position.y, this->position.z));


	// Creating the projection matrix a.k.a perspective view 
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

	// Sending into the shader the updated matrices
	int modelLoc = glGetUniformLocation(this->texture->shader->id, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int viewLoc = glGetUniformLocation(this->texture->shader->id, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	int projectionLoc = glGetUniformLocation(this->texture->shader->id, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



	// Updating the VAO (Vertex Array Object) 
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
