#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {

	class Shader {
	public:

		unsigned int id = 0;

		Shader(const char* vertexSourcePath, const char* fragmentSourcePath);

		void enable();
		void disable();

		void setBoolUniform(const std::string& name, bool value) const;
		void setIntUniform(const std::string& name, int value) const;
		void setFloatUniform(const std::string& name, float value) const;
		void setMat4Uniform(const std::string& name, const glm::mat4& mat) const;
		void setVec3Uniform(const std::string& name, float x, float y, float z) const;
		void setVec3Uniform(const std::string& name, const glm::vec3& vec) const;
		void setVec4Uniform(const std::string& name, const glm::vec4& vec) const;

	};

}