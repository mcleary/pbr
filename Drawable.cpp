#include "Drawable.h"


Drawable::Drawable(std::shared_ptr<Geometry> geometry)
{
	this->geometry = geometry;
}

Drawable::Drawable() :
	Drawable(nullptr)
{
}

glm::mat4 Drawable::modelMatrix() const
{
	return transform.asMatrix();
}
