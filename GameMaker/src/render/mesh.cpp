#include "mesh.h"

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	_vertices = vertices;
	_indices = indices;
	//_textures = textures;

	InitMesh();
}

void Mesh::InitMesh() {
	glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
  
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), 
                 &_vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), 
                 &_indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)0);

    // Vertex Texture Coords
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)offsetof(Vertex, texCoords));

	// Vertex Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

void Mesh::Draw(Texture texture) {
	//for (GLuint i = 0; i < _textures.size(); i++) {
		//Texture tex = _textures[i];
		//texture.Activate();
		//shader.SetTextureSlot("texture_diffuse0", texture.GetTextureID());
		//texture.Bind();
		//std::cout << "used tex" << texture.GetTextureID() << std::endl;
	//}
	//std::cout << "mesh textures " << _textures.size() << std::endl;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//for (GLuint i = 0; i < _textures.size(); i++)
	//{
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	//}
}


Mesh::~Mesh()
{
}
