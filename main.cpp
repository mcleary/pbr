
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

static bool s_bEnableVSync = true;
static int s_WindowWidth = 800;
static int s_WindowHeight = 600;

static Scene* scene = new Scene;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->draw();
}

void key(GLFWwindow* /*window*/, int /*key*/, int /*s*/, int /*action*/, int /*mods*/)
{
    
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
    {
		return;
    }

	if (action == GLFW_PRESS)
	{
        double cursorX, cursorY;
        
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(window, &cursorX, &cursorY);
        
        scene->camera()->mouseButtonEvent(cursorX, cursorY);
	}
	else
    {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mouseMotionCallback(GLFWwindow* window, double x, double y)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
        scene->camera()->mouseMotionEvent(x, y);
    }
}

void mouseScrollCallback(GLFWwindow* /*window*/, double x, double y)
{
    scene->camera()->mouseScrollEvent(x, y);
}

void reshape(GLFWwindow* /*window*/, int width, int height)
{
    scene->camera()->setViewportSize(width, height);
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
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    auto mesh = new SphereMesh(100);
    
    auto simpleMaterial = new SimpleMaterial;
    auto phongMaterial = new PhongMaterial;

    scene->addDrawable(new Sphere({ -1.5, 0.0, 0.0 }, 0.5, mesh, phongMaterial));
	scene->addDrawable(new Sphere({ -0.5, 0.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 0.5, 0.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 1.5, 0.0, 0.0 }, 0.5, mesh, simpleMaterial));
    
    scene->addDrawable(new Sphere({ -1.5, 1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ -0.5, 1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 0.5, 1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 1.5, 1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    
    scene->addDrawable(new Sphere({ -1.5, -1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ -0.5, -1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 0.5, -1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    scene->addDrawable(new Sphere({ 1.5, -1.0, 0.0 }, 0.5, mesh, simpleMaterial));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
}

int main()
{
    GLFWwindow* window = nullptr;
    
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
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mouseMotionCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval( s_bEnableVSync );

	glbinding::Binding::initialize(false);
    
    glfwGetFramebufferSize(window, &s_WindowWidth, &s_WindowHeight);
    reshape(window, s_WindowWidth, s_WindowHeight);

    init();
    
    auto openglVersion = glbinding::ContextInfo::version();
    windowTitleBase += std::to_string(openglVersion.majorVersion()) + "." + std::to_string(openglVersion.minorVersion());
    
    FPSTimer fpsTimer;
    Timer frameTimer;
    
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Draw gears
        draw();
        
        // Update animation
        scene->animate(frameTimer.elapsedSeconds());
        frameTimer.start();
        
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