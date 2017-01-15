#include "SphereAnimator.h"

#include "Sphere.h"

SphereAnimator::SphereAnimator(std::shared_ptr<Sphere> sphere) :
	Animator()
{
	m_Sphere = sphere;
}

void SphereAnimator::update(float deltaTime)
{
	auto& translation = m_Sphere->transform().translation;
	auto& rotation = m_Sphere->transform().rotation;

	translation += m_TranslationSpeed * deltaTime;
	rotation *= glm::quat(m_RotationSpeed * deltaTime);
}
