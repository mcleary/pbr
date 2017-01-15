#pragma once

#include "Animator.h"

#include <glm/glm.hpp>

#include <memory>

class Sphere;


class SphereAnimator : public Animator
{
public:
	explicit SphereAnimator(std::shared_ptr<Sphere> sphere);

	void setRotationSpeed(const glm::vec3& speed);
	void setTranslationSpeed(const glm::vec3& speed);

	virtual void update(float deltaTime) override;

private:
	std::shared_ptr<Sphere> m_Sphere;

	glm::vec3 m_RotationSpeed;
	glm::vec3 m_TranslationSpeed;
};

