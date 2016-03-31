#include "Camera.h"

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
    glm::vec2 rotation = (mouseMotion - m_CursorPosition) / 100.0f;
    m_CursorPosition = mouseMotion;
    
    auto rotationMatrix = glm::rotate(rotation.y, glm::vec3{1, 0, 0}) * glm::rotate(rotation.x, glm::vec3{0, 1, 0});
    auto newEye = rotationMatrix * glm::vec4(m_Eye, 1.0f);
    m_Eye = newEye;
}

void Camera::mouseScrollEvent(float /*x*/, float y)
{
    auto zoom =  (float) y / 4.f;
    auto translateDirection = glm::normalize(m_Eye);
    auto newEye = m_Eye + (translateDirection * -zoom);
    
    if(glm::length(newEye) > 0.4f)
    {
        m_Eye = newEye;
    }
}

glm::mat4 Camera::viewMatrix()
{
	return glm::lookAt(m_Eye, glm::vec3{ 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
}

glm::mat4 Camera::projectionMatrix()
{
    return glm::perspective(45.0f, m_Aspect, 0.01f, 100.0f);
}
