#include "Textures.h"

#include <iostream>

Textures::Textures(/*const char texture_path[]*/std::string texture_path) {
	textureName = texture_path;

	// Generate texture
	glGenTextures(1, &textureID);
	bindTexture();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//stbi_set_flip_vertically_on_load(true);

	// Load texture data
	texture_data = stbi_load(texture_path.c_str(), &width, &height, &colorChannels, 0);
	//std::cout << colorChannels << " ";

	if (colorChannels == 1) {
		colorChannels = GL_RED;
	}
	else if (colorChannels == 3) {
		colorChannels = GL_RGB;
	}else if (colorChannels == 4) {
		colorChannels = GL_RGBA;
	}

	if (texture_data) {
		glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, width, height, 0, colorChannels, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << "Texture_Load_Successful" << std::endl;
	}else std::cout << "Texture_Load_Failed " << textureName << std::endl;

	//--------NEW--------- 16.08.20
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free image memory
	stbi_image_free(texture_data);
}

void Textures::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}