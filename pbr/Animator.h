#pragma once

#include "Drawable.h"

class Animator
{
public:
	explicit Animator(Transform& transform);

	virtual void update(float deltaTime);

	glm::vec3 RotationSpeed;
	glm::vec3 WorldRotationSpeed;

	Transform& transform;
};