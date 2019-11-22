#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

namespace Engine {

	class ShaderHandler {
    private:
        ShaderHandler();
        ~ShaderHandler();
	public:
        static unsigned int createShaderAndCompile(unsigned int type, const char* sourceCode);
        static unsigned int createShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader);
	};

}
