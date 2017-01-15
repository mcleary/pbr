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

		auto material = drawable->material;
		auto program = material->program;

		material->bind();
		program->setUniform("Gamma", m_Gamma);
		program->setUniform("Time", m_CurrentTime);
		program->setUniform("Model", modelMatrix);
		program->setUniform("View", viewMatrix);
		program->setUniform("Projection", projectionMatrix);
		program->setUniform("ViewProjection", viewProjection);
		program->setUniform("ModelView", modelViewMatrix);
		program->setUniform("ModelViewProjection", viewProjection * modelMatrix);
		program->setUniform("NormalMatrix", normalMatrix);

		auto lightViewDir = viewMatrix * glm::vec4{ m_Light->position - drawable->transform.translation, 0.0f };
		program->setUniform("LightPos", glm::vec3{ lightViewPos } / lightViewPos.w);
		program->setUniform("LightWorldPos", m_Light->position);
		program->setUniform("LightDir", glm::normalize(glm::vec3{ lightViewDir }));
		program->setUniform("LightWorldDir", glm::normalize(m_Light->position - drawable->transform.translation));

		drawable->draw();
		material->unbind();
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