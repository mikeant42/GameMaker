#include "shader.h"
#include <fstream>
#include <iostream>


Shader::Shader(std::string vert, std::string frag) {
	vertexId = LoadShader(vert, GL_VERTEX_SHADER);
	fragId = LoadShader(frag, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();

	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragId);

	BindAttribute(0, "position");
	BindAttribute(1, "texCoords");
	BindAttribute(2, "normal"); // not using yet
	BindAttribute(3, "tangent"); // not using yet

	glLinkProgram(programId);

	GLint success;
	GLchar infoLog[512];
	// Check for linking errors
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glValidateProgram(programId);
}

void Shader::BindAttribute(int attrib, const GLchar *name) {
	glBindAttribLocation(programId, attrib, name);
}

void Shader::Start() {
	glUseProgram(programId);
}

void Shader::Stop() {
	glUseProgram(0);
}

void Shader::Cleanup() {
	Stop();

	glDetachShader(programId, fragId);
	glDetachShader(programId, vertexId);

	glDeleteShader(fragId);
	glDeleteShader(vertexId);

	glDeleteProgram(programId);
}

void Shader::LoadFloat(int loc, float var) {
	glUniform1f(loc, var);
}

void Shader::LoadBool(int loc, bool var) {
	glUniform1i(loc, var == false ? 0 : 1); // make sure to check the concencation works
}

void Shader::LoadInt(int loc, int var) {
	glUniform1i(loc, var);
}

void Shader::LoadVec2(int loc, glm::vec2 var) {
	glUniform2f(loc, var.x, var.y);
}

void Shader::LoadVec3(int loc, glm::vec3 var) {
	glUniform3f(loc, var.x, var.y, var.z);
}

void Shader::LoadVec4(int loc, glm::vec4 var) {
	glUniform4f(loc, var.x, var.y, var.z, var.w);
}

void Shader::LoadMat4(int loc, glm::mat4 var) {
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(var));
}

void Shader::SetUniform(const GLchar *name, float value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	} else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadFloat(loc, value);
}

void Shader::SetUniform(const GLchar *name, glm::vec3 value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	}
	else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadVec3(loc, value);
}

void Shader::SetUniform(const GLchar *name, glm::vec2 value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	}
	else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadVec2(loc, value);
}

void Shader::SetUniform(const GLchar *name, bool value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	}
	else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadBool(loc, value);
}

void Shader::SetTextureSlot(const GLchar *name, int value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	}
	else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadInt(loc, value);
}

void Shader::SetUniform(const GLchar *name, glm::mat4 value) {
	int loc;
	if (map.count(name)) {
		loc = map.find(name)->second;
	}
	else {
		loc = glGetUniformLocation(programId, name);
		map.emplace(name, loc);
	}

	LoadMat4(loc, value);
}

Shader::~Shader() {

}

int Shader::LoadShader(std::string name, int type) {
	int shaderId = glCreateShader(type);
	
	std::string text = ProcessShader(name);
	std::cout << text << std::endl;
	const GLchar* shaderCode = text.c_str();

	glShaderSource(shaderId, 1, &shaderCode, NULL);

	glCompileShader(shaderId);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return shaderId;
}

std::string Shader::ProcessShader(std::string name) {
	std::string finalString;
	std::string prefix = "#include";

	try {
		std::ifstream input(name);

		for (std::string line; std::getline(input, line); ) {

			if (!line.compare(0, prefix.size(), prefix)) { // If the line starts with an include
				// For now, this only does #include file instead of #include <file> because w c++ you can't
				// tell the substring where to end.
				finalString += ProcessShader("res/shader/" + line.substr(prefix.length() + 1));
			}
			else {
				finalString += line += "\n";
			}
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Failed to open file. Error: " << std::endl;
	}

	return finalString;
}