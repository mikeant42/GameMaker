#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPos;
out vec3 transposedNormal;
  
void main()
{
	coords = texCoords;
    gl_Position = projection * view * model * vec4(position, 1.0);
	worldPos = vec3(model * vec4(position, 1.0f));
	transposedNormal = mat3(transpose(inverse(model))) * normal;
} 