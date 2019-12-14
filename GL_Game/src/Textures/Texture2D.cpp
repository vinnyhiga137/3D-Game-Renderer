#include "Texture2D.h"


Engine::Texture2D::Texture2D(const char* path) {

	glGenTextures(1, &(this->data));
	glBindTexture(GL_TEXTURE_2D, this->data);

	// Setting the wrap mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Setting the S axis to be mirrored
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Setting the R axis to be mirrored

	// Setting the filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	unsigned char* imageData = stbi_load(path, &(this->width), &(this->height), &(this->colorChannels), 0);


	if (imageData) {

		GLenum format;

		if (this->colorChannels == 1) {
			format = GL_RED;
		}
		else if (this->colorChannels == 3) {
			format = GL_RGB;
		}
		else if (this->colorChannels == 4) {
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "[TEXTURE] Fatal Error! Unable to load image data on array!" << std::endl;
		exit(0);
	}


	stbi_image_free(imageData); // Cleaning on the RAM side the texture's data, it's already on GPU's vRAM!

}





Engine::Texture2D::Texture2D(const char* path, unsigned int type) {

	glGenTextures(1, &(this->data));
	glBindTexture(GL_TEXTURE_2D, this->data);


	// Setting the wrap mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Setting the S axis to be mirrored
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Setting the R axis to be mirrored

	// Setting the filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


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
	std::cout << "[TEXTURE] Fatal Error! Constructor not implementd!" << std::endl;
	exit(0);
}






unsigned int Engine::Texture2D::getData() {
    return this->data;
}
