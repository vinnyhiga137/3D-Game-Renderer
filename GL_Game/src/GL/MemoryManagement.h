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
        /// - VAO: The Vertex Array Object related to construction of a Geometry
        ///
        /// </summary>
		static void generateGeometryBuffer(float* verticesData, size_t vDataSize, unsigned int* VAO);

        static void generateLightEmitterBuffer(float* verticesData, size_t vDataSize, unsigned int* VAO);

	};

}
