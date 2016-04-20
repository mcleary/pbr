#version 330

in vec2 UV;

out vec4 Color;

uniform sampler2D CloudsTexture;

uniform float Time;
uniform vec2 CloudsRotationSpeed = vec2(-0.001, 0.0);

void main()
{
    vec3 cloudsColor = texture(CloudsTexture, UV + Time * CloudsRotationSpeed).rgb;
    Color.rgb = cloudsColor;
    Color.a = 1.0;
}