#include "Camera.h"


Engine::Camera* Engine::Camera::main = 0; // or NULL, or nullptr in c++11

Engine::Camera::Camera() {
	this->position = glm::vec3(0.0f, 0.0f, 5.0f);
}


glm::vec3* Engine::Camera::getPosition() {
	return &(this->position);
}





glm::vec3 Engine::Camera::getFrontVector() {
	return glm::vec3(0.0f, 0.0f, -1.0f);
}





glm::vec3 Engine::Camera::getUpVector() {
	return glm::vec3(0.0f, 1.0f, 0.0f);
}