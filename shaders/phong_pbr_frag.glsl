#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform vec3 LightPos;
uniform vec3 LightDir;
uniform vec3 LightColor = vec3(1.0, 1.0, 1.0);

uniform float Roughness = 0.3;
uniform float F0 = 0.8;
uniform float K = 0.2;

uniform vec3 DiffuseColor;
uniform vec3 SpecularColor = vec3(1.0);
uniform vec3 AmbientColor;
uniform float Shininess;
uniform float Gamma = 1.4;

out vec4 color;

void main()
{
    vec3 normal = normalize(Normal);
    //vec3 lightDir = normalize(LightPos - Position);
	vec3 lightDir = LightDir;
    
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;    	

    if(lambertian > 0.0)
    {
		vec3 viewDir = normalize(-Position);
		vec3 halfDir = normalize(lightDir + viewDir);
		
		float NdotL = lambertian;
		float NdotH = max(dot(normal, halfDir), 0.0);
		float NdotV = max(dot(normal, viewDir), 0.0);
		float VdotH = max(dot(viewDir, halfDir), 0.0);
		float mSquared = Roughness * Roughness;

		// geometric attenuation
        float NH2 = 2.0 * NdotH;
        float g1 = (NH2 * NdotV) / VdotH;
        float g2 = (NH2 * NdotL) / VdotH;
        float geoAtt = min(1.0, min(g1, g2));		

		// roughness (or: microfacet distribution function)
        // beckmann distribution function
        float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
        float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
        float roughness = r1 * exp(r2);

		// fresnel
        // Schlick approximation
        float fresnel = pow(1.0 - VdotH, 5.0);
        fresnel *= (1.0 - F0);
        fresnel += F0;
        
        specular = (fresnel * geoAtt * roughness) / (NdotV * NdotL * 3.14);
    }
    
    vec3 colorLinear = LightColor * lambertian * (K + specular * (1.0 - K));
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma));
    
    color = vec4(colorGammaCorrected, 1.0);
}