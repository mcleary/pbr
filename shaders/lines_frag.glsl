#version 330 core

in vec3 Color;

out vec4 out_Color;

void main()
{
    out_Color = vec4(Color, 1.0);	
}
