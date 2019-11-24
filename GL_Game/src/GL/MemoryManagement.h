#pragma once

#include <glad/glad.h>
#include <iostream>

namespace Engine {

	class MemoryManagement {

	public:
		static void generateGeometryData(float* verticesData, size_t vDataSize, unsigned int* indexes,
			size_t indSize, unsigned int* VAO);

	};

}