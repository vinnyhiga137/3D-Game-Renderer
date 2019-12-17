#include "Material.h"

Engine::Material* Engine::Material::materialList[10];

Engine::Material::Material(std::string name, Color colorParameters,
                           Light lightParameters, std::string shaderName) {

    this->name = name;
    
	this->colorParams = colorParameters;
	this->lightParams = lightParameters;
    
    this->shaderProgram = Engine::Shader::getProgram(shaderName);
    
    // Enabling the shader
	this->shaderProgram->enable();

	// Setting the shader parameters related to Colors
	this->shaderProgram->setIntUniform("material.diffuse", 0);

    this->shaderProgram->setIntUniform("material.specular",
        1);

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

    // Enabling the shader
	this->shaderProgram->enable();

	// Setting the shader parameters related to Colors
	this->shaderProgram->setIntUniform("material.diffuse", 0);

    this->shaderProgram->setIntUniform("material.specular",
        1);

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


	// Binding the texture into the GPU
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->getData());

}




Engine::Material::Material(std::string name, Color colorParameters,
                           Light lightParameters, std::string shaderName, Texture2D* texture,
                           Texture2D* complTexture) {
    
    this->name = name;
     
    this->colorParams = colorParameters;
    this->lightParams = lightParameters;

    this->shaderProgram = Engine::Shader::getProgram(shaderName);
    this->texture = texture;
    this->complTexture = complTexture;

    // Enabling the shader
    this->shaderProgram->enable();

    // Setting the shader parameters related to Colors
    this->shaderProgram->setIntUniform("material.diffuse", 0);

    this->shaderProgram->setIntUniform("material.specular", 1);

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


    // Binding the texture into the GPU
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture->getData());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->complTexture->getData()); // This is generally the specular map
    
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




unsigned int Engine::Material::getComplTextureData() const {
    return this->complTexture->getData();
}




void Engine::Material::update(glm::vec3 lightPosition) {

	this->shaderProgram->updateDynamicData(); // Project, View, ViewPos matrices and vector...

	// Setting the shader parameters related to Colors
	this->shaderProgram->setIntUniform("material.diffuse", 0);

	this->shaderProgram->setIntUniform("material.specular",
		1);

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

	this->shaderProgram->setVec3Uniform("light.position", lightPosition);

	this->lightParams.lightPosition = lightPosition; // Just updating the struct for good practice...
    
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
