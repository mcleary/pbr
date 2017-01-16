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

	glm::vec3 RotationSpeed;
	glm::vec3 TranslationSpeed;

private:
	std::shared_ptr<Drawable> drawable;
};

