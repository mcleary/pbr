#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

class Camera
{
public:
    void setViewportSize(int width, int height);
	
    void mouseButtonEvent(int cursorX, int cursorY);
    void mouseMotionEvent(float x, float y);
    void mouseScrollEvent(float x, float y);

	glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix();

private:
	glm::vec3 m_Eye = { 0.0f, 0.0f, 3.0f };
    glm::vec2 m_CursorPosition = {0.0f, 0.0f};
    float     m_Aspect = 1.0f;
};