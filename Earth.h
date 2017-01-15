#pragma once

#include "Drawable.h"
#include "SphereMesh.h"
#include "Material.h"

class EarthMaterial : public Material
{
public:
	explicit EarthMaterial();

	virtual void bind() override;
	virtual void unbind() override;

private:
	std::shared_ptr<Texture> EarthTexture;
	std::shared_ptr<Texture> OceanMaskTexture;
	std::shared_ptr<Texture> OceanIceTexture;
	std::shared_ptr<Texture> EarthNightTexture;
	std::shared_ptr<Texture> EarthTopographyTexture;
	std::shared_ptr<Texture> CloudsTexture;

};

class Earth : public Drawable
{
public:
	explicit Earth(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh);

	virtual void draw() override;

	float	InnerRadius;
	float	OuterRadius;
	float	RayleighScaleDepth = 0.25f;
	float	ESun = 20.0f;
	float	Kr = 0.0020f;	// Rayleigh scattering constant
	float	Km = 0.0010f;	// Mie scattering constant
	float	g = -0.990f;    // The Mie phase asymmetry factor
	glm::vec3 WaveLength = { 0.650f, 0.570f, 0.475f };

	std::shared_ptr<EarthMaterial> EarthSurfaceMaterial;
};