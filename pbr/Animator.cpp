#include "Animator.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_transform.hpp>

Animator::Animator(Transform& _transform) :
	transform(_transform)
{
}

void Animator::update(float deltaTime)
{
	glm::vec3& translation = transform.translation;
	glm::quat& rotation = transform.rotation;	

	glm::quat ObjectSpaceRotation = glm::quat(RotationSpeed * deltaTime);
	glm::quat WorldSpaceRotation = glm::quat(WorldRotationSpeed * deltaTime);

	rotation *= ObjectSpaceRotation;
	// translation = glm::rotate(WorldSpaceRotation, translation);	
}
