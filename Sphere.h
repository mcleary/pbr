#pragma once

#include "Drawable.h"
#include "SphereMesh.h"

class Sphere : public Drawable
{
public:
	Sphere(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh);

private:
	float m_Radius;
};