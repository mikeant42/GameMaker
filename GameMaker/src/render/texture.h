#pragma once

#include <string>
#include <gl/glew.h>

/*
* Texture class should be extensible and flexible.
*/

class Texture
{
public:
	Texture(int width, int height, unsigned char *imageData, int target, int filter, bool mipMap, int internalFormat, int format, bool clamp);
	Texture(int width, int height, unsigned char *imageData);

	static Texture LoadTexture(std::string fileName);

	void Activate(unsigned int i);
	void Bind();

	inline int GetWidth() {
		return width;
	}
	inline int GetHeight() {
		return height;
	}
	inline GLuint GetTextureID() {
		return id;
	}

	~Texture();

private:
	int width, height, target;
	GLuint id;
	unsigned char *imageData;

};

