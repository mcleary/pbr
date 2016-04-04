#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;
in vec3 N;

out vec4 color;

uniform vec3 LightPos;
uniform vec3 LightDir;

uniform vec3 CameraPos;

uniform float Time;
uniform vec2 CloudsRotationSpeed = vec2(-0.001, 0.0);

uniform sampler2D EarthTexture;
uniform sampler2D NightTexture;
uniform sampler2D CloudsTexture;
uniform sampler2D OceanMaskTexture;
uniform sampler2D TopographyTexture;
uniform sampler2D OceanTexture;

uniform vec3  SpecularColor = vec3(0.5);
uniform float Shininess = 200.0;
uniform float Gamma = 1.2;

void main()
{
    vec3 cloudsColor = texture(CloudsTexture, UV + Time * CloudsRotationSpeed).rgb;
	vec3 earthColor = texture(EarthTexture, UV).rgb;
	vec3 oceanMask = texture(OceanMaskTexture, UV).rgb;
	vec3 nightColor = texture(NightTexture, UV).rgb;
	vec3 oceanColor = texture(OceanTexture, UV).rgb;
	vec3 elevation = texture(TopographyTexture, UV).rgb;

	vec3 normal = normalize(Normal);

    //vec3 sunDir = normalize(LightPos - Position); // For pontual light source
	vec3 sunDir = LightDir;                     // For directional light sources

    float lambertian = max(dot(sunDir, normal), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0)
    {
        vec3 viewDir = normalize(-Position);
        vec3 halfDir = normalize(sunDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, Shininess);
    }

	vec3 earthMask = (1.0 - oceanMask);
	vec3 earthDiffuseColor = lambertian * (earthColor*earthMask + oceanColor*oceanMask) + (1.0 - lambertian) * nightColor;

    vec3 colorLinear = earthDiffuseColor + specular * SpecularColor * oceanMask + cloudsColor * lambertian;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma));
    
    
    // Get the ray from the camera to the vertex and its length (which
    // is the far point of the ray passing through the atmosphere)
    vec3 ray = Position - CameraPos;
    float fFar = length(ray);
    ray /= fFar;
    
    // Calculate the closest intersection of the ray with
    // the outer atmosphere (point A in Figure 16-3)
    

	color = vec4(colorGammaCorrected, 1.0);
}
