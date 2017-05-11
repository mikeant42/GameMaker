#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

private:
	const GLfloat *vertices;
	const GLint *indices;
};

