#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 ModelViewProjection;
uniform mat4 NormalMatrix;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
    vec4 position = View * Model * vec4(in_Position, 1.0);
    
    Position = position.xyz / position.w;
    Normal = vec3(NormalMatrix * vec4(in_Normal, 0.0));
    UV = in_UV;
    
    gl_Position = ModelViewProjection * vec4(in_Position, 1.0);
}
