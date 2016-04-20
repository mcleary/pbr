#version 330

//
// For licensing information, see http://http.developer.nvidia.com/GPUGems/gpugems_app01.html:
//
// NVIDIA Statement on the Software
//
// The source code provided is freely distributable, so long as the NVIDIA header remains unaltered and user modifications are
// detailed.
//
// No Warranty
//
// THE SOFTWARE AND ANY OTHER MATERIALS PROVIDED BY NVIDIA ON THE ENCLOSED CD-ROM ARE PROVIDED "AS IS." NVIDIA DISCLAIMS ALL
// WARRANTIES, EXPRESS, IMPLIED OR STATUTORY, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//
// Limitation of Liability
//
// NVIDIA SHALL NOT BE LIABLE TO ANY USER, DEVELOPER, DEVELOPER'S CUSTOMERS, OR ANY OTHER PERSON OR ENTITY CLAIMING THROUGH OR
// UNDER DEVELOPER FOR ANY LOSS OF PROFITS, INCOME, SAVINGS, OR ANY OTHER CONSEQUENTIAL, INCIDENTAL, SPECIAL, PUNITIVE, DIRECT
// OR INDIRECT DAMAGES (WHETHER IN AN ACTION IN CONTRACT, TORT OR BASED ON A WARRANTY), EVEN IF NVIDIA HAS BEEN ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF THE ESSENTIAL PURPOSE OF ANY
// LIMITED REMEDY. IN NO EVENT SHALL NVIDIA'S AGGREGATE LIABILITY TO DEVELOPER OR ANY OTHER PERSON OR ENTITY CLAIMING THROUGH
// OR UNDER DEVELOPER EXCEED THE AMOUNT OF MONEY ACTUALLY PAID BY DEVELOPER TO NVIDIA FOR THE SOFTWARE OR ANY OTHER MATERIALS.
//

//
// Atmospheric scattering fragment shader
//
// Author: Sean O'Neil
//
// Copyright (c) 2004 Sean O'Neil
//

in vec3 Position;

out vec4 Color;

uniform vec3 LightWorldPos;
uniform vec3 LightWorldDir;
uniform vec3 CameraWorldPos;         // The camera's current position

// Kr is the Rayleigh scattering constant
// Km is the Mie scattering constant
// ESun is the brightness of the sun

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
uniform float Gamma;

uniform float g  = -0.990;	// The Mie phase asymmetry factor
uniform float g2 = 0.9801;	// g*g

const int nSamples = 10;
const float fSamples = float(nSamples);


float scale(float fCos)
{
    float x = 1.0 - fCos;
    return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

float MiePhase(float g, float g2, float q)
{
    return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + q*q) / pow(1.0 + g2 - 2.0 * g * q, 1.5);
}

float RayleighPhase(float fCos)
{
	return 0.75 + 0.75 * fCos * fCos;
}

// Returns the near intersection point of a line and a sphere
float GetNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}

void main (void)
{
    // Get the ray from the camera to the fragment and its length (which is the far point of the ray passing through the atmosphere)
    vec3 v3Pos = Position;
    vec3 v3Ray = v3Pos - CameraWorldPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;	
    
    // Calculate the ray's starting position, then calculate its scattering offset
    vec3 v3Start = vec3(0.0);	
	float fStartOffset = 0.0;

	if(fCameraHeight > fOuterRadius)
	{
		// Camera in space
        
		// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
		float fNear = GetNearIntersection(CameraWorldPos, v3Ray, fCameraHeight2, fOuterRadius2);

		v3Start = CameraWorldPos + v3Ray * fNear;
		fFar -= fNear;
		float fStartAngle = dot(v3Ray, v3Start) / fOuterRadius;
		float fStartDepth = exp(-1.0 / fScaleDepth);
		fStartOffset = fStartDepth * scale(fStartAngle);
	}
	else
	{
		// if camera inside the atmosphere
		v3Start = CameraWorldPos;
		float fHeight = length(v3Start);
		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
		float fStartAngle = dot(v3Ray, v3Start) / fHeight;
		fStartOffset = fDepth*scale(fStartAngle);
	}

    // Initialize the scattering loop variables    
    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * fScale;
    vec3 v3SampleRay = v3Ray * fSampleLength;
    vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
    
    // Now loop through the sample rays
    vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < nSamples; i++)
    {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
        float fLightAngle = dot(LightWorldDir, v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight * 0.99;
        float fScatter = (fStartOffset + fDepth * (scale(fLightAngle) - scale(fCameraAngle)));
        vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }
    vec3 v3Direction = CameraWorldPos - v3Pos;
    float fCos = dot(LightWorldDir, v3Direction) / length(v3Direction);
    float fMiePhase = MiePhase(g, g2, fCos);
	float fRayleightPhase = RayleighPhase(fCos * fCos);
	vec4 c0 = vec4(v3FrontColor * (v3InvWavelength * fKrESun), 1.0);
	vec4 c1 = vec4(v3FrontColor * fKmESun, 1.0);	
	vec4 color = fRayleightPhase * c0 + fMiePhase * c1;    

	Color = color;
	Color.a = color.b; 
   	
    Color.rgb = pow(Color.rgb, vec3(1.0 / Gamma));  // Gamma Correction		
}