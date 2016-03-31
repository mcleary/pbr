#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 Model;
uniform mat4 ModelViewProjection;
uniform mat4 NormalMatrix;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
    vec4 vertPos = Model * vec4(position, 1.0);
    
    Position = vertPos.xyz / vertPos.w;
    Normal = vec3(NormalMatrix * vec4(normal, 0.0));
    UV = uv;
    
    gl_Position = ModelViewProjection * vec4(position, 1.0);
}
