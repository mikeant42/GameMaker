#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "light/light.h"

class Shader
{
public:
	Shader(const std::string &frag, const std::string &vert);
	~Shader();

	void Cleanup();

	void Start();
	void Stop();

	void SetUniform(const GLchar *name, float value);
	void SetUniform(const GLchar *name, const glm::vec3 &value);
	void SetUniform(const GLchar *name, const glm::vec2 &value);
	void SetUniform(const GLchar *name, bool value);
	void SetUniform(const GLchar *name, const glm::mat4 &value);
	void SetTextureSlot(const GLchar *name, int value);
	void SetUniform(const GLchar *name, std::vector<Light> &lights);

private:
	int LoadShader(const std::string &name, int type);
	std::string ProcessShader(const std::string &name);

	int programId;
	int vertexId;
	int fragId;

	std::unordered_map<const GLchar*, int> map;

	void BindAttribute(int attrib, const GLchar *variable);

	void LoadFloat(int loc, float var);
	void LoadBool(int loc, bool var);
	void LoadVec3(int loc, const glm::vec3 &var);
	void LoadVec2(int loc, const glm::vec2 &var);
	void LoadVec4(int loc, const glm::vec4 &var);
	void LoadInt(int loc, int var);
	void LoadMat4(int loc, const glm::mat4 &var);
};

