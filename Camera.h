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

	void keyEvent(int key, int action);

	void keyUpEvent();
	void keyDownEvent();
	void keyLeftEvent();
	void keyRightEvent();

	glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix();
    
    glm::vec3& eye() { return m_Eye; }

	void update(float deltaTime);

private:
	glm::vec3 m_Eye					= {0.0f, 0.0f, 20.0f};
	glm::vec3 m_Pivot 				= {0.0f, 0.0f, 0.0f};    
	glm::vec3 m_Up					= { 0.0f, 1.0f, 0.0f };
    float     m_Aspect			    = 1.0f;

	glm::vec2 m_CursorPosition = { 0.0f, 0.0f };
	float     m_RotationSpeedFactor = 1000.0f;
	float     m_ZoomSpeedFactor     = 10.0f;

	float     m_KeySpeed = 1.5f;
	bool      m_RollRightPressed = false;
	bool      m_UpPressed = false;
	bool	  m_DownPressed = false;
	bool      m_LeftPressed = false;
	bool	  m_RightPressed = false;	
};