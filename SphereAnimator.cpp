#include "SphereAnimator.h"

#include "Sphere.h"

SphereAnimator::SphereAnimator(std::shared_ptr<Drawable> drawable) :
	Animator()
{
	this->drawable = drawable;
}

void SphereAnimator::update(float deltaTime)
{
	auto& transform = drawable->transform;

	auto& translation = transform.translation;
	auto& rotation = transform.rotation;

	translation += TranslationSpeed * deltaTime;
	rotation *= glm::quat(RotationSpeed * deltaTime);	
}
