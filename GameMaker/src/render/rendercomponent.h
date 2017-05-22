#pragma once

#include <GL/glew.h>
#include "../core/component.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include "camera.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>


class RenderComponent : public Component
{
public:
	RenderComponent(const GLchar *path) {
		LoadModel(path);
	}

	~RenderComponent();

	virtual void Input(const InputData &data, float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void Render(Camera *cam);

	inline void SetShader(const Shader &shader) {
		_shader = shader;
	}

	inline Shader GetShader() {
		return _shader;
	}

	inline void AddTexture(const Texture &tex) {
		_textures.push_back(tex);
	}

private:
	void LoadModel(const GLchar *path);
	Shader _shader = Shader("res/shader/default.vert", "res/shader/default.frag");

	std::vector<Mesh> _meshes;
	std::vector<Texture> _textures;

	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

	glm::mat4 model;


};

