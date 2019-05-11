#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	explicit Transform();

	glm::mat4 AsMatrix() const;

	glm::vec3 Translation;
	glm::quat Rotation;
	glm::vec3 Scale;
};
