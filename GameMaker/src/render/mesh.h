#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include "../render/shader.h"
#include "../render/texture.h"

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

	void Draw(Shader shader);

private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	std::vector<Texture> _textures;

	GLuint VAO, VBO, EBO;

	void InitMesh();
};

