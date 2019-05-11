#include "Animator.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_transform.hpp>

Animator::Animator(Transform& Transform) :
	TransformRef(Transform)
{
	RotationSpeed = glm::vec3{ 0.0f };
	WorldRotationSpeed = glm::vec3{ 0.0f };
}

void Animator::Update(float DeltaTime)
{
	glm::vec3& Translation = TransformRef.Translation;
	glm::quat& Rotation = TransformRef.Rotation;

	glm::quat ObjectSpaceRotation{ RotationSpeed * DeltaTime };
	glm::quat WorldSpaceRotation{ WorldRotationSpeed * DeltaTime };

	Rotation *= ObjectSpaceRotation;
	Translation = glm::rotate(WorldSpaceRotation, Translation);	
}
