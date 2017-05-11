#version 330 core

out vec4 color;
uniform vec3 ccolor;
  
void main()
{
    color = vec4(ccolor, 1.0f);
}