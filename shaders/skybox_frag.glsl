#version 330 core

in vec3 TexCoords;

out vec4 Color;

uniform samplerCube SkyboxTexture;

void main()
{
    Color = texture(SkyboxTexture, normalize(TexCoords));		
	Color.a = 1.0;
}
