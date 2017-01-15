#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh) :
	Drawable(mesh)
{
	transform().translation = position;
	transform().scale = glm::vec3{ m_Radius };
}