
#include "Transform.h"

Transform::Transform()
{
	Scale = glm::vec3{ 1.0f };
}

glm::mat4 Transform::AsMatrix() const
{
	return glm::translate(glm::mat4{ 1.0f }, Translation)* glm::toMat4(Rotation)* glm::scale(glm::mat4{ 1.0f }, Scale);
}