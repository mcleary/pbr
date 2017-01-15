#include "Drawable.h"

Drawable::Drawable(std::shared_ptr<Mesh> mesh)
{
	m_Mesh = mesh;
}

glm::mat4 Drawable::modelMatrix() const
{
	return glm::translate(m_Transform.translation) *
		glm::toMat4(m_Transform.rotation) *
		glm::scale(m_Transform.scale);
}

Transform& Drawable::transform()
{
	return m_Transform;
}

void Drawable::draw()
{
	m_Mesh->draw();
}