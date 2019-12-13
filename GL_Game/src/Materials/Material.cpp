#include "Material.h"

Engine::Material* Engine::Material::materialList[10];

Engine::Material::Material(std::string name, Color colorParameters,
                           Light lightParameters, std::string shaderName) {

    this->name = name;
    
	this->colorParams = colorParameters;
	this->lightParams = lightParameters;
    
    this->shaderProgram = Engine::Shader::getProgram(shaderName);
    

	this->shaderProgram->enable();

	// Setting the shader parameters related to Colors
	this->shaderProgram->setVec3Uniform("material.ambient",
		this->colorParams.ambientStrength);

	this->shaderProgram->setVec3Uniform("material.diffuse",
		this->colorParams.diffuseStrength);

	this->shaderProgram->setVec3Uniform("material.specular",
		this->colorParams.specularStrength);

	this->shaderProgram->setFloatUniform("material.shininess",
		this->colorParams.shininess);

	// Setting the shader parameters related to Light
	this->shaderProgram->setVec3Uniform("light.position",
		this->lightParams.lightPosition);

	this->shaderProgram->setVec3Uniform("light.ambient",
		this->lightParams.ambientLightStrength);

	this->shaderProgram->setVec3Uniform("light.diffuse",
		this->lightParams.diffuseLightStrength);

	this->shaderProgram->setVec3Uniform("light.specular",
		this->lightParams.specularLightStrength);

}




Engine::Material::Material(std::string name, Color colorParameters,
                           Light lightParameters, std::string shaderName, Texture2D* texture) {

    this->name = name;
    
	this->colorParams = colorParameters;
	this->lightParams = lightParameters;
	this->shaderProgram = Engine::Shader::getProgram(shaderName);
	this->texture = texture;

}




Engine::Color Engine::Material::getColorParams() const {
	return this->colorParams;
}




Engine::Light Engine::Material::getLightParams() const {
	return this->lightParams;
}




unsigned int Engine::Material::getTextureData() const {
	return this->texture->getData();
}




void Engine::Material::updateLightData(glm::vec3 lightPosition) {
	this->lightParams.lightPosition = lightPosition;
	this->shaderProgram->setVec3Uniform("light.position", lightPosition);
}





Engine::Shader* Engine::Material::getShaderProgram() const {
    return this->shaderProgram;
}





Engine::Material* Engine::Material::getMaterial(std::string name) {
    for (int i = 0; i < 10; i++) {
        if (name.compare(Engine::Material::materialList[i]->name) == 0) {
            return Engine::Material::materialList[i];
        }
    }
    
    return nullptr;
}
