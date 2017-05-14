#include "texture.h"

#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../util/stb_image.h"

Texture::Texture(int width, int height, unsigned char *imageData, int target, int filter, bool mipMap, int internalFormat, int format, bool clamp)
{
	this->width = width;
	this->height = height;
	this->target = target;

	glGenTextures(1, &id);
	glBindTexture(target, id);

	if (mipMap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
	}

	if (clamp) {
		glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(target, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
	
	if (mipMap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

Texture::Texture(int width, int height, unsigned char *imageData) {
	this->imageData = imageData;
	Texture(width, height, imageData, GL_TEXTURE_2D, GL_LINEAR, true, GL_RGBA8, GL_RGBA, true);
}

void Texture::Activate() {
	glActiveTexture(GL_TEXTURE0 + id);
}

void Texture::Bind() {
	glBindTexture(target, id);
}

Texture Texture::LoadTexture(std::string fileName) {
	int w, h, comp;

	stbi_set_flip_vertically_on_load(0);
	unsigned char *image = stbi_load(fileName.c_str(), &w, &h, &comp, STBI_rgb_alpha);

	int width = w;
	int height = h;

	return Texture(width, height, image);
}


Texture::~Texture()
{
}
