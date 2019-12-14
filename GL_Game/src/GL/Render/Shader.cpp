#include "Shader.h"

Engine::Shader* Engine::Shader::shaderList[10];

Engine::Shader::Shader(std::string name, const char* vertexSourcePath, const char* fragmentSourcePath) {

    this->name = name;
    
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
    
    
    // 4TH STEP - Inserting into the Global Vector (List) of Shaders to be shared between the entities!


}



void Engine::Shader::enable() {
	glUseProgram(this->id);
}





void Engine::Shader::updateDynamicData() {

	// Updating the Projection and View Matrices + View Vector Position
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)Engine::Window::getWidth() / (float)Engine::Window::getHeight(),
        0.1f, 100.0f);

    Engine::Camera* mainCamera = Engine::Camera::getInstance();
    
    glm::vec3 position = mainCamera->getPosition();

    this->enable();
    this->setMat4Uniform("projection", projection);

    glm::mat4 view = glm::lookAt(
        position,
        position + mainCamera->getFrontVector(),
        mainCamera->getUpVector());

    this->setMat4Uniform("view", view);
    this->setVec3Uniform("viewPos", mainCamera->getPosition());
}





// TODO: Tacar um tratador para verificar o objeto emite luz...
void Engine::Shader::updateLightEmitterData() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
        (float)Engine::Window::getWidth() / (float)Engine::Window::getHeight(),
        0.1f, 100.0f);

    Engine::Camera* mainCamera = Engine::Camera::getInstance();
    
    glm::vec3 position = mainCamera->getPosition();

    this->enable();
    this->setMat4Uniform("projection", projection);

    glm::mat4 view = glm::lookAt(
        position,
        position + mainCamera->getFrontVector(),
        mainCamera->getUpVector());

    this->setMat4Uniform("view", view);
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

void Engine::Shader::initialSetup(const char* path) {

	// LOADING ALL NECESSARY SHADERS
    char* vertexPath = StringExtension::join(path, "/src/GL/Render/Shaders/Debug_Vertex.vert");
    char* fragPath = StringExtension::join(path, "/src/GL/Render/Shaders/Debug_Fragment.frag");

    Engine::Shader* shader = new Engine::Shader("Debug", vertexPath, fragPath);
    Engine::Shader::shaderList[0] = shader;
}

Engine::Shader* Engine::Shader::getProgram(std::string name) {
    for (int i = 0; i < 10; i++) {
        if (name.compare(Engine::Shader::shaderList[i]->name) == 0) {
            return Engine::Shader::shaderList[i];
        }
    }
    
    return nullptr;
}
