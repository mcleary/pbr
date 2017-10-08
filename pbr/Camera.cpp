#include "Camera.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
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
    auto newUp = rotationMatrix * glm::vec4{ m_Up, 0.0f };

    m_Eye = newEye;
    m_Up = newUp;
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
                m_Up_Pressed = true;
                break;
            case GLFW_KEY_DOWN:
                m_Down_Pressed = true;
                break;
            case GLFW_KEY_LEFT:
                m_Left_Pressed = true;
                break;
            case GLFW_KEY_RIGHT:
                m_Right_Pressed = true;
                break;
            case GLFW_KEY_W:
                m_W_Pressed = true;
                break;
            case GLFW_KEY_A:
                m_A_Pressed = true;
                break;
            case GLFW_KEY_S:
                m_S_Pressed = true;
                break;
            case GLFW_KEY_D:
                m_D_Pressed = true;
                break;
            case GLFW_KEY_Q:
                m_Q_Pressed = true;
                break;
            case GLFW_KEY_E:
                m_E_Pressed = true;
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
                m_Up_Pressed = false;
                break;
            case GLFW_KEY_DOWN:
                m_Down_Pressed = false;
                break;
            case GLFW_KEY_LEFT:
                m_Left_Pressed = false;
                break;
            case GLFW_KEY_RIGHT:
                m_Right_Pressed = false;
                break;
            case GLFW_KEY_W:
                m_W_Pressed = false;
                break;
            case GLFW_KEY_A:
                m_A_Pressed = false;
                break;
            case GLFW_KEY_S:
                m_S_Pressed = false;
                break;
            case GLFW_KEY_D:
                m_D_Pressed = false;
                break;
            case GLFW_KEY_Q:
                m_Q_Pressed = false;
                break;
            case GLFW_KEY_E:
                m_E_Pressed = false;
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
    return glm::perspective(45.0f, m_Aspect, 0.01f, 10000.0f);
}

void Camera::update(float deltaTime)
{
    glm::vec3 viewDirection = glm::normalize(m_Eye - m_Pivot);
    glm::vec3 slideDirection = glm::normalize(glm::cross(viewDirection, m_Up));
    
    glm::vec3 forwardBackwardTranslation = m_KeySpeed * deltaTime * viewDirection;
    glm::vec3 leftRightTranslation = m_KeySpeed * deltaTime * slideDirection * 5.0;
    glm::vec3 upDownTranslation = m_KeySpeed * deltaTime * glm::normalize(m_Up) * 10.0;
    
    if(m_W_Pressed)
    {
        m_Eye -= forwardBackwardTranslation;
		m_Pivot -= forwardBackwardTranslation;
    }
    if(m_S_Pressed)
    {
        m_Eye += forwardBackwardTranslation;
		m_Pivot += forwardBackwardTranslation;
    }
    if(m_A_Pressed)
    {
        m_Eye += leftRightTranslation;
        m_Pivot += leftRightTranslation;
    }
    if(m_D_Pressed)
    {
        m_Eye -= leftRightTranslation;
        m_Pivot -= leftRightTranslation;
    }
    
    if(m_Q_Pressed)
    {
        m_Up = glm::rotate(glm::radians(m_KeySpeed * deltaTime * 10.0f), viewDirection) * glm::vec4{m_Up, 0.0f};
    }
    if(m_E_Pressed)
    {
        m_Up = glm::rotate(glm::radians(m_KeySpeed * deltaTime * 10.0f), -viewDirection) * glm::vec4{m_Up, 0.0f};
    }
    
    if (m_Up_Pressed)
    {
        m_Pivot += upDownTranslation;
    }
    if (m_Down_Pressed)
    {
        m_Pivot -= upDownTranslation;
    }
    if (m_Left_Pressed)
    {
        m_Pivot += leftRightTranslation;
    }
    if (m_Right_Pressed)
    {
        m_Pivot -= leftRightTranslation;
    }
}
