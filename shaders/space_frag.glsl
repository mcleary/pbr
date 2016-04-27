#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 Color;

uniform vec3 LightWorldPos;
uniform vec3 LightWorldDir;
uniform vec3 CameraWorldPos;

uniform vec3  v3InvWavelength;          // 1 / pow(wavelength, 4) for the red, green, and blue channels
uniform float fCameraHeight;
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

uniform sampler2D GroundTexture;


float Scale(float fCos)
{
    float x = 1.0 - fCos;
    return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Returns the near intersection point of a line and a sphere
float GetNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}

// Returns the far intersection point of a line and a sphere
float GetFarIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B + sqrt(fDet));
}

void main()
{
	// Get the ray from the camera to the vertex and its length
	vec3 v3Pos = Position;
    vec3 v3Ray = v3Pos - CameraWorldPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

	GetFarIntersection(v3Pos, v3Ray, float fDistance2, float fRadius2)	

	Color = texture(GroundTexture, UV);
}