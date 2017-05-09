#include "shader.h"
#include <fstream>
#include <iostream>
#include <gl/GL.h>

Shader::Shader(std::string vert, std::string frag) {
	std::cout << ProcessShader(vert);
}

Shader::~Shader() {

}

int Shader::LoadShader(std::string name) {
	int shaderId;
}

std::string Shader::ProcessShader(std::string name) {
	std::string finalString;
	std::string prefix = "#include";

	std::ifstream input(name);
	for (std::string line; std::getline(input, line); ) {
		
		if (!line.compare(0, prefix.size(), prefix)) { // If the line starts with an include
			// For now, this only does #include file instead of #include <file> because w c++ you can't
			// tell the substring where to end.
			finalString += ProcessShader("res/shader/" + line.substr(prefix.length() + 1));
		} else {
			finalString += line += "\n";
		}
	}

	return finalString;
}