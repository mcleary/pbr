#pragma once

#include "Animator.h"

#include <glm/glm.hpp>

#include <memory>

class Sphere;


class SphereAnimator : public Animator
{
public:
	explicit SphereAnimator(std::shared_ptr<Sphere> sphere);

	virtual void update(float deltaTime) override;

private:
	std::shared_ptr<Sphere> sphere;

	glm::vec3 rotationSpeed;
	glm::vec3 translationSpeed;
};

