#pragma once

#include "../Textures/Texture2D.h"
#include "../GL/Render/Shader.h"
#include <glm/vec3.hpp>
#include <string>

namespace Engine {

	struct {
		glm::vec3 ambientLightStrength;
		glm::vec3 diffuseLightStrength;
		glm::vec3 specularLightStrength;
		glm::vec3 lightPosition;
	} typedef Light;

	struct {
		glm::vec3 ambientStrength;
		glm::vec3 diffuseStrength;
		glm::vec3 specularStrength;
		float shininess;
	} typedef Color;

	class Material {
	private:

		Color colorParams;
		Light lightParams;
		Texture2D* texture;

	public:
		
        static Material* materialList[10];
        
        std::string name;
		Shader* shaderProgram;

		Material(std::string name, Color colorParameters, Light lightParameters,
			std::string shaderName);

		Material(std::string name, Color colorParameters, Light lightParameters,
			std::string shaderName, Texture2D* texture);

		Color getColorParams() const;
		Light getLightParams() const;
		unsigned int getTextureData() const;
        Shader* getShaderProgram() const;
		void updateLightData(glm::vec3 lightPosition);
        
        static Material* getMaterial(std::string name);

		
	};
}
