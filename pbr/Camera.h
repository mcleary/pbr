#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    void SetViewportSize(int Width, int Height);
	
    void MouseButtonEvent(float x, float y);
    void MouseMotionEvent(float x, float y);
    void MouseScrollEvent(float x, float y);

	void KeyEvent(int Key, int Action);

	glm::mat4 ViewMatrix();
    glm::mat4 ProjectionMatrix();
    
    glm::vec3& Eye() { return m_Eye; }

	void Update(float DeltaTime);

private:
	glm::vec3 m_Eye					= { 0.0f, 0.0f, 20.0f };
	glm::vec3 m_Pivot 				= { 0.0f, 0.0f, 0.0f };    
	glm::vec3 m_Up					= { 0.0f, 1.0f, 0.0f };
    float     m_Aspect			    = 1.0f;

	glm::vec2 m_CursorPosition      = { 0.0f, 0.0f };
	float     m_RotationSpeedFactor = 1000.0f;
	float     m_ZoomSpeedFactor     = 10.0f;

	float     m_KeySpeed      = 20.0f;
	bool      m_Up_Pressed    = false;
	bool	  m_Down_Pressed  = false;
	bool      m_Left_Pressed  = false;
	bool	  m_Right_Pressed = false;
    bool      m_W_Pressed     = false;
    bool      m_A_Pressed     = false;
    bool      m_S_Pressed     = false;
    bool      m_D_Pressed     = false;
    bool      m_Q_Pressed     = false;
    bool      m_E_Pressed     = false;
};