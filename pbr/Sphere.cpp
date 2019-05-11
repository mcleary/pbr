#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, std::shared_ptr<SphereMesh> mesh, std::shared_ptr<Material> material) :
	Drawable(mesh)
{
	this->radius = radius;
	this->material = material;

	transform.Translation = position;
	transform.Scale = glm::vec3{ this->radius };
}

void Sphere::draw()
{
	material->bind();
	material->bindParams(materialParams);
	Mesh->draw();
}