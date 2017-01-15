#include "Drawable.h"

glm::mat4 Transform::asMatrix() const
{
	return glm::translate(translation) * glm::toMat4(rotation) * glm::scale(scale);
}

Drawable::Drawable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
	this->mesh = mesh;
	this->material = material;
}

glm::mat4 Drawable::modelMatrix() const
{
	return transform.asMatrix();
}

void Drawable::draw()
{
	mesh->draw();
}