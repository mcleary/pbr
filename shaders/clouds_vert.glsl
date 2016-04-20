#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec2 in_UV;

out vec2 UV;

uniform mat4 Model;
uniform mat4 ViewProjection;
uniform float fCloudLayerRadius;

void main(void)
{
    UV = in_UV;
    
    vec4 position = Model * vec4(in_Position * fCloudLayerRadius, 1.0);
    gl_Position = ViewProjection * position;
}