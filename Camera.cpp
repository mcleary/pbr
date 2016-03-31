#include "Camera.h"

#include <glm/ext.hpp>

void Camera::setRotation(float alpha, float beta)
{
	// Move back
	//glTranslatef(0.0, 0.0, -zoom);
	//// Rotate the view
	//glRotatef(beta, 1.0, 0.0, 0.0);
	//glRotatef(alpha, 0.0, 0.0, 1.0);

	//glm::mat4 rotation = glm::rotate(alpha, glm::vec3{ 0.0f, 0.0f, 1.0f }) * glm::rotate(beta, glm::vec3{ 1.0f, 0.0f, 0.0f });
	//glm::mat4 rotation = glm::mat4(1.0f);
	
	m_Eye = glm::rotateX(m_Eye, beta);
	m_Eye = glm::rotateZ(m_Eye, alpha);	
}

void Camera::setZoom(float zoom)
{
	m_Eye.z = zoom;
}

glm::mat4 Camera::getModelView()
{
	return glm::lookAt(m_Eye, glm::vec3{ 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
}
