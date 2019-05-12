#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "Drawable.h"
#include "Light.h"
#include "Camera.h"
#include "Animator.h"

class Scene
{
public:

	explicit Scene();

	void AddDrawable(std::shared_ptr<Drawable> drawable);
	void AddAnimator(std::shared_ptr<Animator> animator);

	std::shared_ptr<Camera> camera() const;

	void Draw();
	void Update(float deltaTime);

	std::shared_ptr<Light> TheLight;

private:
	std::vector<std::shared_ptr<Drawable>> m_Drawables;	
	std::shared_ptr<Camera>                m_Camera;
	std::vector<std::shared_ptr<Animator>> m_Animators;
	float								   m_CurrentTime	= 0.0f;
	float								   m_Gamma			= 1.2f;
};