#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	void setRotation(float alpha, float beta);
	void setZoom(float zoom);

	glm::mat4 getModelView();

private:
	glm::vec3 m_Eye = { 0.0f, 0.0f, 2.0f };
};