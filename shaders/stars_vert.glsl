#version 330 core

layout (location = 0) in vec3 in_Position;

uniform mat4 ModelViewProjection;
uniform mat4 ViewProjection;

void main()
{	
    gl_Position = ModelViewProjection * vec4(in_Position, 1.0); 
}  
