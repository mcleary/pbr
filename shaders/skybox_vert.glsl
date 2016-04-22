#version 330 core

layout (location = 0) in vec3 in_Position;

out vec3 TexCoords;

uniform mat4 View;
uniform mat4 Projection;

void main()
{
	TexCoords = in_Position;
    gl_Position = Projection * mat4(mat3(View)) * vec4(in_Position, 1.0);    
}  
