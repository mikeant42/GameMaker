#version 330 core

out vec4 color;
uniform vec3 ccolor;

in vec2 coords;

uniform sampler2D texSampler;
  
void main()
{
    color = texture(texSampler, coords);
}