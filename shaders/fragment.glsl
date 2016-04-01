#version 330 core

in vec3 Normal;
in vec2 UV;

out vec4 color;

void main()
{
    color = vec4(normalize(Normal), 1.0);
}
