#include "meshrenderer.h"

//#include "light/light.h"

#include <iostream>

void MeshRenderer::Render(Camera *cam, std::vector<Light> lights)
{
	model = glm::mat4();
	model = glm::translate(model, GetParent()->GetTransform()->GetPosition());
	model = glm::scale(model, glm::vec3(GetParent()->GetTransform()->GetScale()));
	//GLfloat angle = 20.0f;
	//model = glm::rotate(model, (GLfloat)(glfwGetTime() * 100.0f) / 50, glm::vec3(0.5f, 1.0f, 0.0f));

	_shader.Start();

	_shader.SetUniform("model", model);
	_shader.SetUniform("view", cam->GetView());
	_shader.SetUniform("projection", cam->GetProjection());
	_shader.SetUniform("camPos", cam->GetTransform()->GetPosition());
	_shader.SetUniform("lights", lights);

	_shader.SetUniform("albedo", mat.albedo);
	_shader.SetUniform("ao", mat.ao);
	_shader.SetUniform("metallic", mat.metallic);
	_shader.SetUniform("roughness", mat.roughness);

	for (GLuint i = 0; i < _meshes.size(); i++) {
		_meshes[i].Draw(_shader);
	}

	_shader.Stop();
}

void MeshRenderer::LoadModel(const GLchar *path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	
	//directory = path.substr(0, path.find_last_of('/'));

	this->ProcessNode(scene->mRootNode, scene);

}

void MeshRenderer::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(ProcessMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh MeshRenderer::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// Process vertex positions, normals and texture coordinates
		
		glm::vec3 pos = glm::vec3();
		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;

		glm::vec3 normal = glm::vec3();
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertex.position = pos;
		vertex.normal = normal;	


		vertices.push_back(vertex);
	}

	
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
		// Process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = this->LoadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = this->LoadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		else {
			textures = _textures;
		}
		std::cout << _textures.size();

	return Mesh(vertices, indices, _textures);
}

std::vector<Texture> MeshRenderer::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
	std::string typeName)
{
	std::vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		// Let's use aiTextureType and typeName when I have a good material class going.

		Texture texture = Texture::LoadTexture(str.C_Str());

		textures.push_back(texture);
	}
	return textures;
}

MeshRenderer::~MeshRenderer()
{
}
