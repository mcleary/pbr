#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec3 lightPos;

uniform vec3 DiffuseColor;
uniform vec3 SpecularColor = vec3(1.0);
uniform vec3 AmbientColor;
uniform float Shininess;
uniform float Gamma;

out vec4 color;

vec3 FresnelSchlick(vec3 SpecularColor, vec3 E, vec3 H)
{
    return SpecularColor + (1.0f - SpecularColor) * pow(1.0f - clamp(dot(E, H), 0.0, 1.0), 5.0);
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;
    vec3 schlick = vec3(0.0);
    
    if(lambertian > 0.0)
    {
        vec3 viewDir = normalize(-Position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, Shininess);

		vec3 L = lightDir;
		vec3 H = halfDir;
		float SpecularPower = Shininess;
		float dotNL = lambertian;
		vec3 N = normal;
		schlick = FresnelSchlick(SpecularColor, L, H) * ((SpecularPower + 2.0) / 8.0) * pow(clamp(dot(N, H), 0.0, 1.0), SpecularPower) * dotNL;
    }
    
    vec3 colorLinear = AmbientColor + lambertian * DiffuseColor + specular * SpecularColor;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma));
    
    color = vec4(schlick, 1.0);
}