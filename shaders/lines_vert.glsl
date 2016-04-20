#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;

uniform mat4 ViewProjection;

out vec3 Color;

void main()
{    
	Color = in_Color;
	gl_Position = ViewProjection * vec4(in_Position, 1.0);	
}
