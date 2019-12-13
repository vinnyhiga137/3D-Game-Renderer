#include "Material.h"

Engine::Material::Material(Color colorParameters, Light lightParameters,
	Shader* shaderProgram) {

	this->colorParams = colorParameters;
	this->lightParams = lightParameters;
	this->shaderProgram = shaderProgram;

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




Engine::Material::Material(Color colorParameters, Light lightParameters, 
	Shader* shaderProgram, Texture2D* texture) {

	this->colorParams = colorParameters;
	this->lightParams = lightParameters;
	this->shaderProgram = shaderProgram;
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