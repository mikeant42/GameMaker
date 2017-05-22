#version 330 core

out vec4 color;

in vec2 coords;

uniform sampler2D textureSampler0;
  
void main()
{
    color = texture(textureSampler0, coords);
	//color = vec4(1,1,1,1);
}