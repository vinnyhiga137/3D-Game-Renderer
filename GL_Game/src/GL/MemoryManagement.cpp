#include "MemoryManagement.h"

void Engine::MemoryManagement::generateGeometryData(float* verticesData, size_t vDataSize, unsigned int* indexes,
	size_t indSize, unsigned int* VAO)
{

	unsigned int VBO;

	glGenVertexArrays(1, VAO);      // Creating "one" Vertex Array Object
	glGenBuffers(1, &VBO);			// Creating "one" Vertex Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(*VAO);													       // Signalizing to GPU that "VAO" must be used now

	glBindBuffer(GL_ARRAY_BUFFER, VBO);											   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, vDataSize, verticesData, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data


	// TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Setting the first pointer to read parameters related to POSITION
	glEnableVertexAttribArray(0);                                                 // Saying which vertex attrib must be handled (which is ZERO)

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

