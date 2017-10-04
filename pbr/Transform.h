#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	glm::mat4 asMatrix() const;

	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1.0);
};

inline glm::mat4 Transform::asMatrix() const
{
    return glm::translate(glm::mat4(1.0), translation) * glm::toMat4(rotation) * glm::scale(scale);
}
