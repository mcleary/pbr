#version 330 core

in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform sampler2D Texture;

void main()
{
    vec4 textureColor = texture(Texture, UV);
    
    color = textureColor;
}
