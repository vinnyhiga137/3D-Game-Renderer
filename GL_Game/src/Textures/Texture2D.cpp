#include "Texture2D.h"

Engine::Texture2D::Texture2D(const char* path, Shader* shader) {

	this->shader = shader;


	glGenTextures(1, &(this->data));
	glBindTexture(GL_TEXTURE_2D, this->data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // Setting the S axis to be mirrored
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // Setting the R axis to be mirrored


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(path, &(this->width), &(this->height), &(this->colorChannels), 0);


	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error! Unable to load image data on array!" << std::endl;
		this->data = 0;
	}


	stbi_image_free(imageData); // Cleaning on the RAM side the texture's data, it's already on GPU's vRAM!

}




Engine::Texture2D::Texture2D(const char* path, unsigned int type, Shader* shader) {
	
	this->shader = shader;


	glGenTextures(1, &(this->data));
	glBindTexture(GL_TEXTURE_2D, this->data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // Setting the S axis to be mirrored
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // Setting the R axis to be mirrored


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(path, &(this->width), &(this->height), &(this->colorChannels), 0);


	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, type, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error! Unable to load image data on array!" << std::endl;
		this->data = 0;
	}


	stbi_image_free(imageData); // Cleaning on the RAM side the texture's data, it's already on GPU's vRAM!

}

Engine::Texture2D::Texture2D() {
	throw "Fatal! Constructor not implementd!";
}
