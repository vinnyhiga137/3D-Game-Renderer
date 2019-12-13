#pragma once

//#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <STB/stb_image.h>
#include <iostream>

namespace Engine {

	class Texture2D {
    private:
        unsigned int data;

        int width, height;
        int colorChannels;
        
	public:

		/// <summary>
		/// Basic constructor.
		/// This constructor returns into {data} the image buffer supporting channels of type RGB and without Alpha.
		///
		/// PARAMETERS:
		/// - path: Absolute path to the desired file.
		///			The file must be of type JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC.
		///
		/// </summary>
		Texture2D(const char* path);


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
		Texture2D(const char* path, unsigned int type);

		/// <summary>
		/// Default constructor.
		/// </summary>
		Texture2D();
        
        /// <summary>
        /// This methods gets the texture data.
        ///
        /// </summary>
        unsigned int getData();

	};

}
