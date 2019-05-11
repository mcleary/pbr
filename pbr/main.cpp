#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glbinding/Version.h>

#include <glbinding-aux/ContextInfo.h>
#include <glbinding-aux/types_to_string.h>

#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

// #include <memory>

#include "Timer.h"
#include "Scene.h"
#include "Sphere.h"
#include "PhongMaterial.h"
#include "Earth.h"
#include "Moon.h"
#include "Axis.h"
#include "Animator.h"

static int  s_WindowWidth  = 800;
static int  s_WindowHeight = 600;
static bool s_bEnableVSync = true;
static bool s_bWireframe   = false;
static bool s_bFullScreen = false;

static std::shared_ptr<Scene> scene = std::make_shared<Scene>();

using namespace gl;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->draw();
}

void key(GLFWwindow* /*window*/, int key, int /*s*/, int action, int /*mods*/)
{
	scene->camera()->KeyEvent(key, action);

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_L:
			//scene->toggleLightAnimation();
			break;
		case GLFW_KEY_K:
			//scene->toggleLightDirection();
			break;
		case GLFW_KEY_O:
			s_bWireframe = !s_bWireframe;
			glPolygonMode(GL_FRONT_AND_BACK, s_bWireframe ? GL_LINE : GL_FILL);			
			std::cout << "Wireframe: " << s_bWireframe << std::endl;
			break;		
		default:
			break;
		}		
	}
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
        
        scene->camera()->MouseButtonEvent(static_cast<int>(cursorX), static_cast<int>(cursorY));
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
        scene->camera()->MouseMotionEvent(static_cast<float>(x), static_cast<float>(y));
    }
}

void mouseScrollCallback(GLFWwindow* /*window*/, double x, double y)
{
    scene->camera()->MouseScrollEvent(static_cast<float>(x), static_cast<float>(y));
}

void reshape(GLFWwindow* /*window*/, int width, int height)
{
	if (width > 0 && height > 0)
	{
		scene->camera()->SetViewportSize(width, height);
		glViewport(0, 0, (GLint)width, (GLint)height);
	}    
}

static void createScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	auto phongMaterial = std::make_shared<PhongMaterial>();
	auto sphereMesh = std::make_shared<SphereMesh>(200);
    
    glm::vec3 earthPosition{ 0.0f };
    float earthRadius = 6.371f;
    
    glm::vec3 moonPosition{ 200.4f, 0.0f, 0.0f };
    float moonRadius = 10.737f;

    auto earth = std::make_shared<Earth>(earthPosition, earthRadius, sphereMesh);
    auto moon = std::make_shared<Moon>(moonPosition, moonRadius, sphereMesh);
	auto axis = std::make_shared<Axis>();

	float MoonRotationSpeed = 0.3f;

    auto moonAnimator = std::make_shared<Animator>(moon->transform);
    // moonAnimator->RotationSpeed.z = MoonRotationSpeed;
//    moonAnimator->WorldRotationSpeed.y = -MoonRotationSpeed;

//    auto sunAnimator = std::make_shared<Animator>(scene->light->transform);
//    sunAnimator->WorldRotationSpeed.y = -0.00f;

    scene->addAnimator(moonAnimator);
//    scene->addAnimator(sunAnimator);

	// Order is important here. Earth must be the last
    scene->addDrawable(moon);
    scene->addDrawable(earth);
    scene->addDrawable(axis);
}

static void init()
{
    // OpenGL Initialization
    using namespace std;
	using namespace glbinding;

    cout << "OpenGL Version: " << endl;
    cout << "\tGL_RENDERER: " << glbinding::aux::ContextInfo::renderer() << endl;
    cout << "\tGL_VERSION : " << glbinding::aux::ContextInfo::version().toString() << endl;
    cout << "\tGL_VENDOR  : " << glbinding::aux::ContextInfo::vendor() << endl;	

	Binding::setCallbackMaskExcept(CallbackMask::After, { "glGetError" });		
	Binding::setAfterCallback([](const FunctionCall &)
	{
		const GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "error: " << error << std::endl;
	});
	/*setCallbackMask(CallbackMask::After | CallbackMask::ParametersAndReturnValue);
	glbinding::setAfterCallback([](const glbinding::FunctionCall & call)
	{
		std::cout << call.function->name() << "(";
		for (unsigned i = 0; i < call.parameters.size(); ++i)
		{
			std::cout << call.parameters[i]->asString();
			if (i < call.parameters.size() - 1)
				std::cout << ", ";
		}
		std::cout << ")";

		if (call.returnValue)
			std::cout << " -> " << call.returnValue->asString();

		std::cout << std::endl;
	});*/
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);   
	
	createScene();
}

int main()
{
    GLFWwindow* window = nullptr;
    
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
    }
    
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
    glfwWindowHint(GLFW_SAMPLES, 16);

    std::string windowTitleBase = "Physically Based Rendering with OpenGL ";	
    
	if (s_bFullScreen)
	{
		int monitorsCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorsCount);
		const int activeMonitorIdx = 1;

		const GLFWvidmode* mode = glfwGetVideoMode(monitors[activeMonitorIdx]);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(mode->width, mode->height, windowTitleBase.data(), monitors[activeMonitorIdx], nullptr);
	}
	else
	{
		window = glfwCreateWindow(s_WindowWidth, s_WindowHeight, windowTitleBase.data(), nullptr, nullptr);
	}
    
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
    glfwSwapInterval(s_bEnableVSync);

	glbinding::Binding::initialize(glfwGetProcAddress);
    
    glfwGetFramebufferSize(window, &s_WindowWidth, &s_WindowHeight);
    reshape(window, s_WindowWidth, s_WindowHeight);

    init();
    
    const glbinding::Version openglVersion = glbinding::aux::ContextInfo::version();
    windowTitleBase += openglVersion.toString();
    
    FPSTimer fpsTimer;
    Timer frameTimer;
    
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {        
        draw();
        
        // Update animation
        scene->update(static_cast<float>(frameTimer.ElapsedSeconds()));
        
        frameTimer.Start();
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        if(fpsTimer.Update())
        {
            const std::string windowTitle = windowTitleBase + " - FPS: " + std::to_string(fpsTimer.GetFPS());
            glfwSetWindowTitle(window, windowTitle.data());
        }
    }
    
    // Terminate GLFW
    glfwTerminate();
    
    // Exit program
    return EXIT_SUCCESS;
}
