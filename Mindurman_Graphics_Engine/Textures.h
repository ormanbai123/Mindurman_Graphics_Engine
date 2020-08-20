#pragma once

#include "stb_image.h"
#include <GL/glew.h>

#include <string>

class Textures {

public:
	Textures(/*const char texture_path[]*/std::string texture_path);

	void bindTexture();

	inline GLuint getTextureID() { return textureID; };
private:
	int width = 0; int height = 0; int colorChannels = 0;

	GLuint textureID = 0;

	unsigned char* texture_data = nullptr;

	std::string textureName;
};