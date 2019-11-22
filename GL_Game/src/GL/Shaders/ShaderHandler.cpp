#include "ShaderHandler.h"

#ifdef MAC_OS
#define GL_SILENCE_DEPRECATION
#endif

unsigned int Engine::ShaderHandler::createShaderAndCompile(unsigned int type, const char* sourceCode) {

    unsigned int shader;
    shader = glCreateShader(type);

    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

unsigned int Engine::ShaderHandler::createShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader) {

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, *vertexShader);
    glAttachShader(shaderProgram, *fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shaderProgram;
}
