#version 330 core

in vec3 TexCoords;

out vec4 Color;

uniform samplerCube SkyboxTexture;

void main()
{
    Color = texture(SkyboxTexture, normalize(TexCoords));
	Color.x = 0.4;
	//Color = vec4(TexCoords, 1.0);
}
