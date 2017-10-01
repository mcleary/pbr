#include "Animator.h"

#include <glm/gtx/matrix_decompose.hpp>

Animator::Animator(Transform& _transform) :
	transform(_transform)
{
}

void Animator::update(float deltaTime)
{
	auto& translation = transform.translation;
	auto& rotation = transform.rotation;	

	auto ObjectSpaceRotation = glm::quat(RotationSpeed * deltaTime);
	auto WorldSpaceRotation = glm::quat(WorldRotationSpeed * deltaTime);

	rotation *= ObjectSpaceRotation;
	translation = glm::rotate(WorldSpaceRotation, translation);
}
