#include "Drawable.h"


glm::mat4 Transform::asMatrix() const
{
	return glm::translate(translation) * glm::toMat4(rotation) * glm::scale(scale);
}

Drawable::Drawable(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;	
}

Drawable::Drawable() :
	Drawable(nullptr)
{
}

glm::mat4 Drawable::modelMatrix() const
{
	return transform.asMatrix();
}
