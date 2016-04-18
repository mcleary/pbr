#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;
in vec3 N;

out vec4 color;

uniform vec3 LightWorldPos;
uniform vec3 LightWorldDir;
uniform vec3 CameraWorldPos;

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

uniform vec3  v3InvWavelength;          // 1 / pow(wavelength, 4) for the red, green, and blue channels
uniform float fCameraHeight2;           // fCameraHeight^2
uniform float fOuterRadius;			    // The outer (atmosphere) radius
uniform float fOuterRadius2;			// fOuterRadius^2
uniform float fInnerRadius;				// The inner (planetary) radius
uniform float fKrESun;					// Kr * ESun
uniform float fKmESun;					// Km * ESun
uniform float fKr4PI;					// Kr * 4 * PI
uniform float fKm4PI;					// Km * 4 * PI
uniform float fScale;					// 1 / (fOuterRadius - fInnerRadius)
uniform float fScaleDepth;				// The scale depth (i.e. the altitude at which the atmosphere's average density is found)
uniform float fScaleOverScaleDepth;		// fScale / fScaleDepth

const int nSamples = 10;
const float fSamples = float(nSamples);

float scale(float fCos)
{
    float x = 1.0 - fCos;
    return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Returns the near intersection point of a line and a sphere
float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}

void main()
{	
    vec3 cloudsColor = texture(CloudsTexture, UV + Time * CloudsRotationSpeed).rgb;
	vec3 earthColor = texture(EarthTexture, UV).rgb;
	vec3 oceanMask = texture(OceanMaskTexture, UV).rgb;
	vec3 nightColor = texture(NightTexture, UV).rgb;
	vec3 oceanColor = texture(OceanTexture, UV).rgb;
	vec3 elevation = texture(TopographyTexture, UV).rgb;	

	// Get the ray from the camera to the fragment and its length (which is the far point of the ray passing through the atmosphere)
    vec3 v3Pos = Position;
    vec3 v3Ray = v3Pos - CameraWorldPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

	// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
    float fNear = getNearIntersection(CameraWorldPos, v3Ray, fCameraHeight2, fOuterRadius2);
	
	// Calculate the ray's starting position, then calculate its scattering offset
    vec3 v3Start = CameraWorldPos + v3Ray * fNear;
    fFar -= fNear;
	float fDepth = exp((fInnerRadius - fOuterRadius) / fScaleDepth);
	float fCameraAngle = dot(-v3Ray, v3Pos) / length(v3Pos);
	float fLightAngle = dot(LightWorldDir, v3Pos) / length(v3Pos);
	float fCameraScale = scale(fCameraAngle);
	float fLightScale = scale(fLightAngle);
	float fCameraOffset = fDepth*fCameraScale;
	float fTemp = (fLightScale + fCameraScale);	
	
	// Initialize the scattering loop variables
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

	// Now loop through the sample rays
	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	vec3 v3Attenuate = vec3(0.0);
	for(int i=0; i<nSamples; i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
		float fScatter = fDepth*fTemp - fCameraOffset;
		v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	vec3 v3ScatteringPrimaryColor = v3FrontColor * (v3InvWavelength * fKrESun + fKmESun);	
	vec3 v3ScatteringColor = v3ScatteringPrimaryColor + 0.25 * v3Attenuate;
	
	vec3 normal = normalize(Normal);

    //vec3 lightDir = normalize(LightPos - Position); // For pontual light source
	vec3 lightDir = LightWorldDir;						  // For directional light sources
    
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;
    
    if(lambertian > 0.0)
    {
        vec3 viewDir = normalize(-Position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, Shininess);
    }		
	
	vec3 earthMask = (1.0 - oceanMask);	
	vec3 earthDiffuseColor = lambertian * (earthColor*earthMask + oceanColor*oceanMask) + (1.0 - lambertian) * nightColor;	
    
    vec3 colorLinear = earthDiffuseColor + specular * SpecularColor * oceanMask + cloudsColor * lambertian;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / Gamma)); 

	color = vec4(colorGammaCorrected, 1.0);	

	color = vec4(v3ScatteringColor, 1.0);	
}
