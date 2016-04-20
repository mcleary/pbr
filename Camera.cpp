#include "Camera.h"

#include <GLFW/glfw3.h>

#include <glm/ext.hpp>
#include <algorithm>

void Camera::setViewportSize(int width, int height)
{
    m_Aspect = width / static_cast<float>(height);
}

void Camera::mouseButtonEvent(int cursorX, int cursorY)
{
    m_CursorPosition = {cursorX, cursorY};
}

void Camera::mouseMotionEvent(float x, float y)
{
    glm::vec2 mouseMotion{x, y};
    glm::vec2 rotation = (mouseMotion - m_CursorPosition) / m_RotationSpeedFactor;
    m_CursorPosition = mouseMotion;
    
    auto rotationMatrix = glm::rotate(-rotation.y, glm::vec3{1, 0, 0}) * glm::rotate(-rotation.x, glm::vec3{0, 1, 0});
    auto newEye = rotationMatrix * glm::vec4{ m_Eye, 1.0f };
    m_Eye = newEye;
}

void Camera::mouseScrollEvent(float /*x*/, float y)
{
    auto zoom =   y / m_ZoomSpeedFactor;
    auto translateDirection = glm::normalize(m_Eye);
    auto newEye = m_Eye + (translateDirection * -zoom);
    
    if(glm::length(newEye) > 0.4f)
    {
        m_Eye = newEye;
    }
}

void Camera::keyEvent(int key, int action)
{	
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			m_UpPressed = true;
			break;
		case GLFW_KEY_DOWN:
			m_DownPressed = true;
			break;
		case GLFW_KEY_LEFT:
			m_LeftPressed = true;
			break;
		case GLFW_KEY_RIGHT:
			m_RightPressed = true;
			break;		
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			m_UpPressed = false;
			break;
		case GLFW_KEY_DOWN:
			m_DownPressed = false;
			break;
		case GLFW_KEY_LEFT:
			m_LeftPressed = false;
			break;
		case GLFW_KEY_RIGHT:
			m_RightPressed = false;
			break;
		default:
			break;
		}
	}
}

glm::mat4 Camera::viewMatrix()
{
	return glm::lookAt(m_Eye, m_Pivot, m_Up);
}

glm::mat4 Camera::projectionMatrix()
{
    return glm::perspective(45.0f, m_Aspect, 0.01f, 1000.0f);
}

void Camera::update(float deltaTime)
{
	if (m_UpPressed)
	{
		m_Pivot.y += m_KeySpeed * deltaTime;
	}
	if (m_DownPressed)
	{
		m_Pivot.y -= m_KeySpeed * deltaTime;
	}
	if (m_LeftPressed)
	{
		m_Pivot.x -= m_KeySpeed * deltaTime;
	}
	if (m_RightPressed)
	{
		m_Pivot.x += m_KeySpeed * deltaTime;
	}
}
