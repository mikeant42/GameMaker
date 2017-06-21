#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include "../render/shader.h"
#include "../render/texture.h"

#include <iostream>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(Texture texture);

	//inline void AddTexture(const Texture &tex) {
	//	_textures.push_back(tex);
	//}

	//inline void SetTexture(const Texture &tex) {
	//	texture = tex;
	//}

private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	//std::vector<Texture> _textures;
	//Texture texture = Texture::LoadTexture("res/texture/white.png");

	GLuint VAO, VBO, EBO;

	void InitMesh();
};

