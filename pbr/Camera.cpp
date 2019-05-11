#include "Camera.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

void Camera::SetViewportSize(int Width, int Hight)
{
    m_Aspect = Width / static_cast<float>(Hight);
}

void Camera::MouseButtonEvent(int CursorX, int CursorY)
{
    m_CursorPosition = {CursorX, CursorY};
}

void Camera::MouseMotionEvent(double x, double y)
{
    glm::vec2 mouseMotion{x, y};
    glm::vec2 rotation = (mouseMotion - m_CursorPosition) / m_RotationSpeedFactor;
    m_CursorPosition = mouseMotion;
    
    glm::mat4 rotationMatrix = glm::rotate(-rotation.y, glm::vec3{1, 0, 0}) * glm::rotate(-rotation.x, glm::vec3{0, 1, 0});	

    m_Eye = rotationMatrix * glm::vec4{ m_Eye, 1.0f };
    m_Up = rotationMatrix * glm::vec4{ m_Up, 0.0f };
}

void Camera::MouseScrollEvent(double /*x*/, double y)
{
    auto zoom =   y / m_ZoomSpeedFactor;
    auto translateDirection = glm::normalize(m_Eye);
    auto newEye = m_Eye + (translateDirection * -zoom);
    
    if(glm::length(newEye) > 0.4f)
    {
        m_Eye = newEye;
    }
}

void Camera::KeyEvent(int Key, int Action)
{
    if (Action == GLFW_PRESS)
    {
        switch (Key)
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
    else if (Action == GLFW_RELEASE)
    {
        switch (Key)
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

glm::mat4 Camera::ViewMatrix()
{
    return glm::lookAt(m_Eye, m_Pivot, m_Up);
}

glm::mat4 Camera::ProjectionMatrix()
{
    return glm::perspective(45.0f, m_Aspect, 0.01f, 10000.0f);
}

void Camera::Update(float deltaTime)
{
    glm::vec3 ViewDirection = glm::normalize(m_Eye - m_Pivot);
    glm::vec3 SlideDirection = glm::normalize(glm::cross(ViewDirection, m_Up));
    
    glm::vec3 ForwardBackwardTranslation = m_KeySpeed * deltaTime * ViewDirection;
    glm::vec3 LeftRightTranslation = m_KeySpeed * deltaTime * SlideDirection * 5.0;
    glm::vec3 UpDownTranslation = m_KeySpeed * deltaTime * glm::normalize(m_Up) * 10.0;
    
    if(m_W_Pressed)
    {
        m_Eye -= ForwardBackwardTranslation;
		m_Pivot -= ForwardBackwardTranslation;
    }
    if(m_S_Pressed)
    {
        m_Eye += ForwardBackwardTranslation;
		m_Pivot += ForwardBackwardTranslation;
    }
    if(m_A_Pressed)
    {
        m_Eye += LeftRightTranslation;
        m_Pivot += LeftRightTranslation;
    }
    if(m_D_Pressed)
    {
        m_Eye -= LeftRightTranslation;
        m_Pivot -= LeftRightTranslation;
    }
    
    if(m_Q_Pressed)
    {
        m_Up = glm::rotate(glm::radians(m_KeySpeed * deltaTime * 10.0f), ViewDirection) * glm::vec4{m_Up, 0.0f};
    }
    if(m_E_Pressed)
    {
        m_Up = glm::rotate(glm::radians(m_KeySpeed * deltaTime * 10.0f), -ViewDirection) * glm::vec4{m_Up, 0.0f};
    }
    
    if (m_Up_Pressed)
    {
        m_Pivot += UpDownTranslation;
    }
    if (m_Down_Pressed)
    {
        m_Pivot -= UpDownTranslation;
    }
    if (m_Left_Pressed)
    {
        m_Pivot += LeftRightTranslation;
    }
    if (m_Right_Pressed)
    {
        m_Pivot -= LeftRightTranslation;
    }
}
