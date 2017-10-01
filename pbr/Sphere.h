#pragma once

#include "Drawable.h"
#include "SphereMesh.h"
#include "Material.h"

class Sphere : public Drawable
{
public:
	Sphere(
		glm::vec3 position, 
		float radius, 
		std::shared_ptr<SphereMesh> mesh, 
		std::shared_ptr<Material>	material
	);

	virtual void draw() override;

	float radius;
	std::shared_ptr<SphereMesh> Mesh;
	std::shared_ptr<Material>	material;
};