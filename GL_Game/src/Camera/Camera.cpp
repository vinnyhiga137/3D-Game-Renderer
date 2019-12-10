#include "Camera.h"


Engine::Camera* Engine::Camera::main = nullptr;





Engine::Camera::Camera() {
	this->position = glm::vec3(0.0f, 0.0f, 5.0f);
    this->rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
    this->frontVector = glm::vec3(0.0, 0.0, -1.0f);
}






glm::vec3 Engine::Camera::getPosition() {
	return this->position;
}






void Engine::Camera::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}






void Engine::Camera::setPosition(glm::vec3 position) {
    this->position = position;
}






glm::vec3 Engine::Camera::getRotation() {
    return this->rotation;
}





void Engine::Camera::setRotation(float x, float y, float z) {

    this->rotation = glm::vec3(x, y, z);
    
    glm::vec3 newFrontVector;
    
    // OBSERVATION related to the 'rotation' values:
    // The X axis is the Yaw angle
    // The Y axis is the Pitch angle
    // The Z won't be used for the Roll angle
    
    newFrontVector.x = cos(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));
    newFrontVector.y = sin(glm::radians(this->rotation.y));
    newFrontVector.z = sin(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));

    newFrontVector = glm::normalize(newFrontVector);
    
    this->frontVector = newFrontVector;
    
}




void Engine::Camera::setRotation(glm::vec3 rotation) {

    this->rotation = rotation;
    
    glm::vec3 newFrontVector;
    
    // OBSERVATION related to the 'rotation' values:
    // The X axis is the Yaw angle
    // The Y axis is the Pitch angle
    // The Z won't be used for the Roll angle
    
    newFrontVector.x = cos(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));
    newFrontVector.y = sin(glm::radians(this->rotation.y));
    newFrontVector.z = sin(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));
    
    newFrontVector = glm::normalize(newFrontVector);
    
    this->frontVector = newFrontVector;
}







glm::vec3 Engine::Camera::getFrontVector() {
    return this->frontVector;
}





glm::vec3 Engine::Camera::getUpVector() {
	return glm::vec3(0.0f, 1.0f, 0.0f);
}
