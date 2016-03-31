
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>
using namespace gl;

#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

#include "Timer.h"
#include "Drawables.h"
#include "Shader.h"
#include "Camera.h"

static bool s_bEnableVSync = true;
static int s_WindowWidth = 800;
static int s_WindowHeight = 600;

Shader* vertexShader = nullptr;
Shader* fragShader = nullptr;
Program* program = nullptr;

Scene scene;
Camera camera;

GLfloat cameraZoom;
GLfloat alpha = 210.f, beta = -70.f;
double cursorX;
double cursorY;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

    program->bind();

	auto mvLoc = glGetUniformLocation(program->m_ProgramID, "ModelView");
	auto projLoc = glGetUniformLocation(program->m_ProgramID, "Projection");
	glm::mat4 proj = glm::perspective(60.0f, s_WindowWidth / (float)s_WindowHeight, 0.1f, 10.0f);
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	scene.draw();
    program->unbind();
}

void key(GLFWwindow* /*window*/, int /*key*/, int /*s*/, int /*action*/, int /*mods*/)
{
    
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;

	if (action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &cursorX, &cursorY);
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		alpha = (GLfloat)(x - cursorX) / 100.f;
		beta = (GLfloat)(y - cursorY) / 100.f;

		cursorX = x;
		cursorY = y;

		camera.setRotation(alpha, beta);
	}
}


//========================================================================
// Callback function for scroll events
//========================================================================

void scroll_callback(GLFWwindow* window, double x, double y)
{
	cameraZoom -= (float) y / 4.f;
	if (cameraZoom < 0)
	{
		cameraZoom = 0;
	}		
	camera.setZoom(cameraZoom);
}


void reshape(GLFWwindow* window, int width, int height)
{
	/*GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 1.0f;
	zfar = 300.0f;
	xmax = znear * 0.5f;*/

	glViewport(0, 0, (GLint)width, (GLint)height);	
}

static void init()
{
    // OpenGL Initialization
    using namespace std;

    cout << "OpenGL Version: " << endl;
    cout << "\tGL_RENDERER: " << glbinding::ContextInfo::renderer() << endl;
    cout << "\tGL_VERSION : " << glbinding::ContextInfo::version() << endl;
    cout << "\tGL_VENDOR  : " << glbinding::ContextInfo::vendor() << endl;
    
    glClearColor(0.0, 0.0, 0.0, 1.0);	

	vertexShader = new Shader(ShaderType::ShaderType_VERTEX, "shaders/vertex.glsl");
	fragShader = new Shader(ShaderType::ShaderType_FRAGMENT, "shaders/fragment.glsl");

	program = new Program;
    program->attach(vertexShader);
    program->attach(fragShader);
    program->link();

	scene.addDrawable(new Sphere({ 0.0, 0.0, 0.0 }, 1.0, 20.0));
}

int main()
{
    GLFWwindow* window;    
    
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
    }
    
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

#ifdef __APPLE__    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    std::string windowTitleBase = "Physically Based Rendering with OpenGL ";
    
    window = glfwCreateWindow( s_WindowWidth, s_WindowHeight, windowTitleBase.data(), nullptr, nullptr );
    if (!window)
    {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // Set callback functions
    glfwSetFramebufferSizeCallback(window, reshape);
    glfwSetKeyCallback(window, key);
	glfwSetMouseButtonCallback(window, mouse_button_callback);	
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval( s_bEnableVSync );

	glbinding::Binding::initialize(false);
    
    glfwGetFramebufferSize(window, &s_WindowWidth, &s_WindowHeight);
    reshape(window, s_WindowWidth, s_WindowHeight);

    init();
    
    auto openglVersion = glbinding::ContextInfo::version();
    windowTitleBase += std::to_string(openglVersion.majorVersion()) + "." + std::to_string(openglVersion.minorVersion());
    
    FPSTimer fpsTimer;
    
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Draw gears
        draw();
        
        // Update animation
//        animate();
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        if(fpsTimer.update())
        {
            auto windowTitle = windowTitleBase + " - FPS: " + std::to_string(fpsTimer.getFPS());
            glfwSetWindowTitle(window, windowTitle.data());
        }	
    }
    
    // Terminate GLFW
    glfwTerminate();
    
    // Exit program
    return EXIT_SUCCESS;
}