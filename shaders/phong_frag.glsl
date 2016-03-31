#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec3 lightPos;

uniform vec3 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 AmbientColor;
uniform float Shininess;
uniform float Gamma;

out vec4 color;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;
    
    if(lambertian > 0.0)
    {
        vec3 viewDir = normalize(-Position);
        
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, Shininess);
    }
    
    vec3 colorLinear = AmbientColor + lambertian * DiffuseColor + specular * SpecularColor;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma));
    
    color = vec4(colorGammaCorrected, 1.0);
}