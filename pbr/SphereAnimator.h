#pragma once

#include "Animator.h"

#include <glm/glm.hpp>

#include <memory>

class Drawable;

class SphereAnimator : public Animator
{
public:
	explicit SphereAnimator(std::shared_ptr<Drawable> drawable);

	virtual void update(float deltaTime) override;	

	
	glm::vec3 WorldRotationSpeed;

private:
	std::shared_ptr<Drawable> drawable;
};

