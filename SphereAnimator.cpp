#include "SphereAnimator.h"

#include "Sphere.h"

SphereAnimator::SphereAnimator(std::shared_ptr<Drawable> drawable) :
	Animator()
{
	this->drawable = drawable;
}

void SphereAnimator::update(float deltaTime)
{
	auto& translation = drawable->transform.translation;
	auto& rotation = drawable->transform.rotation;

	translation += TranslationSpeed * deltaTime;
	rotation *= glm::quat(RotationSpeed * deltaTime);	
}
