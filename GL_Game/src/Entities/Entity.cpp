#include "Entity.h"
#include <GLFW\glfw3.h>

Engine::Entity::Entity(float x, float y, Texture2D* texture) {

	Vector2 position;
	position.x = x;
	position.y = y;

	this->position = position;

	this->texture = texture;


	float verticesData[] = {
		// positions          // colors           // texture coords
		0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right (0)
		0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right (1)
	   -0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left (2)
	   -0.25f,  0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left (3)
	};

	unsigned int indexes[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	Engine::MemoryManagement::generateGeometryData(verticesData, sizeof(verticesData), indexes, sizeof(indexes), &(this->VAO));


}

void Engine::Entity::draw() {

	glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, this->texture->data);
	glUniform1i(glGetUniformLocation(this->texture->shader->id, "uTexture"), 0); // Setting the texture into the Uniform variable

	this->texture->shader->enable();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(this->position.x, this->position.y, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(this->texture->shader->id, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
