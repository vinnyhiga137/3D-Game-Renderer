#pragma once

//#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <STB/stb_image.h>
#include <iostream>
#include "../GL/Render/Shader.h"

namespace Engine {

	class Texture2D {
	public:

		unsigned int data;

		int width, height;
		int colorChannels;
		Shader* shader;

		/// <summary>
		/// Basic constructor.
		/// This constructor returns into {data} the image buffer supporting channels of type RGB and without Alpha.
		///
		/// PARAMETERS:
		/// - path: Absolute path to the desired file.
		///			The file must be of type JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC.
		///
		/// </summary>
		Texture2D(const char* path, Shader* shader);

		/// <summary>
		/// Constructor with channel type argument.
		/// This constructor returns into {data} the image buffer supporting channels of desired type.
		///
		/// PARAMETERS:
		/// - path: Absolute path to the desired file.
		///			The file must be of type JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC.
		///
		/// - type: The type of the channels supported by OpenGL 3.3 version.
		///
		/// </summary>
		Texture2D(const char* path, unsigned int type, Shader* shader);

		/// <summary>
		/// Default constructor.
		/// </summary>
		Texture2D();

		~Texture2D();
	};

}