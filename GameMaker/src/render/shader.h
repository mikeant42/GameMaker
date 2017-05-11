#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(std::string frag, std::string vert);
	~Shader();

	void Cleanup();

	void Start();
	void Stop();

	void SetUniform(const GLchar *name, float value);
	void SetUniform(const GLchar *name, glm::vec3 value);
	void SetUniform(const GLchar *name, glm::vec2 value);
	void SetUniform(const GLchar *name, bool value);
	void SetUniform(const GLchar *name, glm::mat4 value);
	void SetTextureSlot(const GLchar *name, int value);

private:
	int LoadShader(std::string name, int type);
	std::string ProcessShader(std::string name);

	int programId;
	int vertexId;
	int fragId;

	std::unordered_map<const GLchar*, int> map;

	void BindAttribute(int attrib, const GLchar *variable);

	void LoadFloat(int loc, float var);
	void LoadBool(int loc, bool var);
	void LoadVec3(int loc, glm::vec3 var);
	void LoadVec2(int loc, glm::vec2 var);
	void LoadVec4(int loc, glm::vec4 var);
	void LoadInt(int loc, int var);
	void LoadMat4(int loc, glm::mat4 var);
};

