#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_UV;

uniform mat4 NormalMatrix;
uniform mat4 ModelViewProjection;

out vec3 Normal;
out vec2 UV;

void main()
{
    Normal = vec3(NormalMatrix * vec4(in_Normal, 0.0));
    UV = in_UV;
	gl_Position = ModelViewProjection * vec4(in_Position, 1.0);	
}
