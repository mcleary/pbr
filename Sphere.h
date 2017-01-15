#pragma once

#include "Drawable.h"
#include "SphereMesh.h"

class Sphere : public Drawable
{
public:
	Sphere(
		glm::vec3 position, 
		float radius, 
		std::shared_ptr<SphereMesh> mesh, 
		std::shared_ptr<Material>	material
	);

private:
	float m_Radius;
};