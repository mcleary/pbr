
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>
using namespace gl;

#include <GLFW/glfw3.h>

#include "Timer.h"
#include "Sphere.h"
#include "Shader.h"

static bool s_bEnableVSync = true;

Sphere* sphere = nullptr;

const std::string vertexShaderSrc = "\
#version 330 core \n\
layout(location = 0) in vec3 position; \
layout(location = 1) in vec3 normal; \
layout(location = 2) in vec2 uv; \
out vec3 v_normal; \
out vec2 v_uv; \
void main() \
{ \
    v_normal = normal; \
    v_uv = uv; \
	gl_Position = vec4(position, 1.0); \
}";

const std::string fragShaderSrc = "\
#version 330 core \n\
in vec3 v_normal; \
in vec2 v_uv; \
out vec4 color; \
void main() \
{ \
    color = vec4(normalize(v_uv), 0.0, 1.0); \
}";

Shader* vertexShader = nullptr;
Shader* fragShader = nullptr;
Program* program = nullptr;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    program->bind();
	sphere->draw();
    program->unbind();
}

void key(GLFWwindow* /*window*/, int /*key*/, int /*s*/, int /*action*/, int /*mods*/)
{
    
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

	sphere = new Sphere({ 0.0, 0.0, 0.0 }, 1.0, 20.0);

	vertexShader = new Shader(ShaderType::ShaderType_VERTEX, vertexShaderSrc);
	fragShader = new Shader(ShaderType::ShaderType_FRAGMENT, fragShaderSrc);

	program = new Program;
    program->attach(vertexShader);
    program->attach(fragShader);
    program->link();
}

int main()
{
    GLFWwindow* window;
    int width = 800, height = 600;
    
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fprintf( stderr, "Failed to initialize GLFW\n" );
        
    }
    
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

#ifdef __APPLE__    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    std::string windowTitleBase = "Physically Based Rendering with OpenGL ";
    
    window = glfwCreateWindow( width, height, windowTitleBase.data(), nullptr, nullptr );
    if (!window)
    {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // Set callback functions
    glfwSetFramebufferSizeCallback(window, reshape);
    glfwSetKeyCallback(window, key);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval( s_bEnableVSync );

	glbinding::Binding::initialize(false);
    
    glfwGetFramebufferSize(window, &width, &height);
    reshape(window, width, height);

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