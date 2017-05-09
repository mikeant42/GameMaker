#pragma once

#include <string>
#include <map>

class Shader
{
public:
	Shader(std::string frag, std::string vert);
	~Shader();

private:
	int LoadShader(std::string name);
	std::string ProcessShader(std::string name);
	int programId;
	int vertexId;
	int fragID;
	std::map<std::string, int> map;
};

