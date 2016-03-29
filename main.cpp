
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <GLFW/glfw3.h>

#include "Timer.h"
#include "Sphere.h"
#include "Shader.h"

static bool s_bEnableVSync = true;

Sphere* sphere = nullptr;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};
GLuint vbo;
GLuint vao;

const std::string vertexShaderSrc = "\
#version 330 core \
layout(location = 0) in vec3 position; \
layout(location = 1) in vec3 normal; \
layout(location = 2) in vec2 uv; \
smooth out vec3 v_normal; \
smooth out vec2 v_uv; \
void main() \
{ \
    v_normal = normal; \
    v_uv = uv; \
	gl_Position = vec4(position, 1.0); \
}";

const std::string fragShaderSrc = "\
#version 330 core \
smooth in vec3 v_normal; \
smooth in vec2 v_uv; \
out vec4 color; \
void main() \
{ \
    color = vec4(normalize(v_uv.xy), 1.0, 1.0); \
}";

Shader* vertexShader = nullptr;
Shader* fragShader = nullptr;
Program* program = nullptr;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    program->bind();
    
	sphere->draw();
    
//	glBindVertexArray(vao);	
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	glBindVertexArray(0);
    
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
    cout << "\tGL_RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "\tGL_VERSION:  " << glGetString(GL_VERSION) << endl;
    cout << "\tGL_VENDO: " << glGetString(GL_VENDOR) << endl;    
    
    glClearColor(0.0, 0.0, 0.0, 1.0);

	sphere = new Sphere({ 0.0, 0.0, 0.0 }, 1.0, 10.0);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	glBindVertexArray(0);

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
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
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
//    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( s_bEnableVSync );

	glbinding::Binding::initialize(false);
    
    glfwGetFramebufferSize(window, &width, &height);
    reshape(window, width, height);

    init();
    
    int majorVersion;
    int minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    
    windowTitleBase += std::to_string(majorVersion) + "." + std::to_string(minorVersion);
    
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