#include "Shader.h"

Engine::Shader::Shader(const char* vertexSourcePath, const char* fragmentSourcePath) {

	std::string vertexCode;
	std::string fragmentCode;

	// 1ST STEP - Load the source codes

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	// TODO: What this does?
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Reading the source codes
	try {

		// Opening files (.frag and .vert)
		vertexFile.open(vertexSourcePath);
		fragmentFile.open(fragmentSourcePath);

		std::stringstream vertexStream, fragmentStream;

		// Transfering the bytes into the respective streams
		vertexStream   << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		// Converting the streams into strings
		vertexCode   = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "[ERROR] Cannot read shader file!" << std::endl;
		return;
	}

	const char* vertexCodePtr = vertexCode.c_str();
	const char* fragmentCodePtr = fragmentCode.c_str();


	// 2ND STEP - Compile the shaders

	unsigned int vertex, fragment;

	int success;
	char log[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCodePtr, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << "Error! Could not compile VERTEX SHADER!\n" << log << std::endl;
		return;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCodePtr, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success) {
		glDeleteShader(vertex);
		glGetShaderInfoLog(fragment, 512, NULL, log);
		std::cout << "Error! Could not compile FRAGMENT SHADER!\n" << log << std::endl;
		return;
	}

	// 3RD STEP - Create the Shader Program
	this->id = glCreateProgram();
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);

	// Checking for linking errors
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, log);
		std::cout << "Error! Could not LINK the Shader Program!\n" << log << std::endl;
	}

}



void Engine::Shader::enable() {
	glUseProgram(this->id);
}

void Engine::Shader::setBoolUniform(const std::string& name, bool value) const {

	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniform1i(address, (int) value);
}

void Engine::Shader::setIntUniform(const std::string& name, int value) const {

	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniform1i(address, value);
}

void Engine::Shader::setFloatUniform(const std::string& name, float value) const {

	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniform1f(address, value);
}

void Engine::Shader::setMat4Uniform(const std::string& name, const glm::mat4& mat) const {

	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniformMatrix4fv(address, 1, GL_FALSE, &mat[0][0]);
}

void Engine::Shader::setVec3Uniform(const std::string& name, float x, float y, float z) const {

	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniform3f(address, x, y, z);
}

void Engine::Shader::setVec3Uniform(const std::string& name, const glm::vec3& vec) const {
	
	GLint address = glGetUniformLocation(this->id, name.c_str());
	
	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}

	glUniform3fv(address, 1, &vec[0]);
}

void Engine::Shader::setVec4Uniform(const std::string& name, const glm::vec4& vec) const {
	
	GLint address = glGetUniformLocation(this->id, name.c_str());

	if (address == -1) {
		std::cout << "[SHADER] Fatal Error! Couldn't find the desired variable " << name << "!" << std::endl;
		exit(0);
	}
	
	glUniform4fv(address, 1, &vec[0]);
}