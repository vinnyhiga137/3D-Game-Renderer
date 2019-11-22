#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {

	class Shader {
	public:

		unsigned int id;

		Shader(const char* vertexSourcePath, const char* fragmentSourcePath);

		void enable();
		void disable();

		void setBoolUniform(const std::string& name, bool value) const;
		void setIntUniform(const std::string& name, int value) const;
		void setFloatUniform(const std::string& name, float value) const;
	};

}