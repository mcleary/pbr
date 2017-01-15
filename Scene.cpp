#include "Scene.h"

Scene::Scene()
{
	m_Light = std::make_shared<Light>(glm::vec3{ 0.0f, 0.0f, 300.0f });
	m_Camera = std::make_shared<Camera>();
}

void Scene::addDrawable(std::shared_ptr<Drawable> drawable)
{
	m_Drawables.push_back(drawable);
}

void Scene::addAnimator(std::shared_ptr<Animator> animator)
{
	m_Animators.push_back(animator);
}

std::shared_ptr<Camera> Scene::camera() const
{
	return m_Camera;
}

void Scene::draw()
{

}

void Scene::update(float deltaTime)
{
	m_CurrentTime += deltaTime;

	for (auto animator : m_Animators)
	{
		animator->update(deltaTime);
	}

	m_Camera->update(deltaTime);
}