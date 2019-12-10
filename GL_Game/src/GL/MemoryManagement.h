#pragma once

#include <glad/glad.h>
#include <iostream>

namespace Engine {

	class MemoryManagement {

	public:
        
        /// <summary>
        /// This methods generates the Geometry Data, by sending information into a Vertex Array Object.
        ///
        /// PARAMETERS:
        /// - verticesData: The vertices position in an array
        ///
        /// - vDataSize: The size of the array related to vertices position
        ///
        /// - indexes: The indexes of the vertices to form a triangle
        ///
        /// - indSize: The size of the array related to the indexes of each vertex
        ///
        /// - VAO: The Vertex Array Object related to construction of a Geometry
        ///
        /// </summary>
		static void generateGeometryData(float* verticesData, size_t vDataSize, unsigned int* indexes,
			size_t indSize, unsigned int* VAO);

	};

}
