#pragma once

#include "Drawable.h"
#include "SphereMesh.h"
#include "Material.h"

class MoonMaterial : public Material
{
public:
	explicit MoonMaterial();

	virtual void bind() override;
	virtual void unbind() override {}

private:
	std::shared_ptr<Texture> MoonTexture;
	std::shared_ptr<Texture> MoonBumpTexture;
};

class Moon : public Drawable
{
public:
	explicit Moon(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh);

	virtual void draw() override;

	float Radius;

	std::shared_ptr<SphereMesh>		MoonMesh;
	std::shared_ptr<MoonMaterial>	MoonMat;
};