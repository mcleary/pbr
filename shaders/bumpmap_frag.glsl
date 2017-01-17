#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 color;

uniform sampler2D DiffuseTexture;
uniform sampler2D BumpMapTexture;

uniform vec3 DiffuseColor = vec3(1.0);
uniform vec3 SpecularColor = vec3(0.0);
uniform vec3 AmbientColor = vec3(0.0);
uniform float Shininess = 320.0;
uniform float Gamma;

uniform vec3 LightPos;

void main()
{
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

    vec3 DiffuseTextureColor = texture(DiffuseTexture, UV).rgb;
    vec3 BumpValue = texture(BumpMapTexture, UV).rgb;

    vec3 FinalDiffuseColor = DiffuseColor * DiffuseTextureColor;
    
    vec3 colorLinear = AmbientColor + lambertian * FinalDiffuseColor + specular * SpecularColor;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma));
    
    color = vec4(colorGammaCorrected, 1.0);
}
