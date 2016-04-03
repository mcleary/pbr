#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform vec3 LightPos;

uniform sampler2D EarthTexture;
uniform sampler2D CloudsTexture;
uniform sampler2D WaterTexture;

uniform vec4  SpecularColor = vec4(1.0);
uniform float Shininess = 60.0;
uniform float Gamma = 1.4;

void main()
{
    vec4 earthColor = texture(EarthTexture, UV);
    vec4 cloudsColor = texture(CloudsTexture, UV);
	vec4 waterColor = texture(WaterTexture, UV);
	
	vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(LightPos - Position);
    
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;
    
    if(lambertian > 0.0)
    {
        vec3 viewDir = normalize(-Position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, Shininess);
    }	
    
    vec4 colorLinear = lambertian * (earthColor) + specular * SpecularColor * waterColor;
    vec4 colorGammaCorrected = pow(colorLinear, vec4(1.0 / Gamma));
    
    color = colorGammaCorrected;
}
