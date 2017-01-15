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
	auto projectionMatrix = m_Camera->projectionMatrix();
	auto viewMatrix = m_Camera->viewMatrix();
	auto viewProjection = projectionMatrix * viewMatrix;

	glm::vec4 lightViewPos = viewMatrix * glm::vec4{ m_Light->position, 1.0f };

	for (auto drawable : m_Drawables)
	{
		auto modelMatrix = drawable->modelMatrix();
		auto modelViewMatrix = viewMatrix * modelMatrix;
		auto normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

		drawable->materialParams.set("Gamma", m_Gamma);
		drawable->materialParams.set("Time", m_CurrentTime);
		drawable->materialParams.set("Model", modelMatrix);
		drawable->materialParams.set("View", viewMatrix);
		drawable->materialParams.set("Projection", projectionMatrix);
		drawable->materialParams.set("ViewProjection", viewProjection);
		drawable->materialParams.set("ModelView", modelViewMatrix);
		drawable->materialParams.set("ModelViewProjection", viewProjection * modelMatrix);
		drawable->materialParams.set("NormalMatrix", normalMatrix);

		auto lightViewDir = viewMatrix * glm::vec4{ m_Light->position - drawable->transform.translation, 0.0f };
		drawable->materialParams.set("LightPos", glm::vec3{ lightViewPos } / lightViewPos.w);
		drawable->materialParams.set("LightWorldPos", m_Light->position);
		drawable->materialParams.set("LightDir", glm::normalize(glm::vec3{ lightViewDir }));
		drawable->materialParams.set("LightWorldDir", glm::normalize(m_Light->position - drawable->transform.translation));

		drawable->draw();
	}
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