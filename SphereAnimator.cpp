#include "SphereAnimator.h"

#include "Sphere.h"

SphereAnimator::SphereAnimator(std::shared_ptr<Sphere> sphere) :
	Animator()
{
	this->sphere = sphere;
}

void SphereAnimator::update(float deltaTime)
{
	auto& translation = sphere->transform.translation;
	auto& rotation = sphere->transform.rotation;

	translation += translationSpeed * deltaTime;
	rotation *= glm::quat(rotationSpeed * deltaTime);
}
