#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh, std::shared_ptr<Material> material) :
	Drawable(mesh, material)
{
	m_Radius = radius;

	transform.translation = position;
	transform.scale = glm::vec3{ m_Radius };
}