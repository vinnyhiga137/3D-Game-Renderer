#pragma once

#include <glad/glad.h>

#include "../../GL/MemoryManagement.h"
#include "../../Materials/Material.h"
#include "../../GL/Render/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
    namespace Debug {

    // WARNING! This a debug class! Do not use in production environment!
    // There are workarounds on the following functions!
    class Lamp {
        
    private:
        
        // Attributes
        unsigned int VAO;
        Shader* shaderProgram;
        glm::vec3 position;
        
    public:
        
        Lamp(glm::vec3 position, Shader* shaderProgram);
        
        void setPosition(glm::vec3 position);
        glm::vec3 getPosition();
        Engine::Shader* getShaderProgram();
        void draw();
    };


    }

}
