#include "MemoryManagement.h"

void Engine::MemoryManagement::generateGeometryData(float* verticesData, size_t vDataSize, unsigned int* indexes,
	size_t indSize, unsigned int* VAO)
{

	unsigned int VBO, EBO;

	glGenVertexArrays(1, VAO);      // Creating "one" Vertex Array Object
	glGenBuffers(1, &EBO);			// Creating "one" Element Buffer Object
	glGenBuffers(1, &VBO);			// Creating "one" Vertex Buffer Object

	// WARNING! We must bind the VAO first before anything related to VBO
	glBindVertexArray(*VAO);													       // Signalizing to GPU that "VAO" must be used now

	glBindBuffer(GL_ARRAY_BUFFER, VBO);											   // Signalizing to GPU that "VBO" must be used now
	glBufferData(GL_ARRAY_BUFFER, vDataSize, verticesData, GL_STATIC_DRAW); // Sending to the memory buffer the VBO's data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);									   // Signalizing to GPU that "EBO" must be used now
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indexes, GL_STATIC_DRAW);   // Sending to the memory buffer the EBO's data

	// TELLING THE GPU HOW TO INTERPRET THE VERTEX SHADER ATTRIBUTES
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Setting the first pointer to read parameters related to POSITION
	glEnableVertexAttribArray(0);                                                 // Saying which vertex attrib must be handled (which is ZERO)

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Setting the first pointer to read parameters related to POSITION
	glEnableVertexAttribArray(1);																	// Saying which vertex attrib must be handled (which is ONE)

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

