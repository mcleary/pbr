#include "Light.h"

Light::Light(glm::vec3 position)
{
	m_Position = position;
}

glm::vec3 & Light::position()
{
	return m_Position;
}
