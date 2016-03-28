
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <GLFW/glfw3.h>

#include "Timer.h"

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void key(GLFWwindow* window, int key, int s, int action, int mods)
{
    
}

void reshape(GLFWwindow* window, int width, int height)
{
    
}

static void init()
{
    // OpenGL Initialization
    using namespace std;

    cout << "OpenGL Version: " << endl;
    cout << "\tGL_RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "\tGL_VERSION:  " << glGetString(GL_VERSION) << endl;
    cout << "\tGL_VENDO: " << glGetString(GL_VENDOR) << endl;
    //cout << "\tGL_EXTENSIONS: " << glGetString(GL_EXTENSIONS) << endl;
    
    glClearColor(1.0, 0.0, 0.0, 1.0);
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
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glbinding::Binding::initialize();
    
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
    glfwSwapInterval( 1 );
    
    glfwGetFramebufferSize(window, &width, &height);
    reshape(window, width, height);

    init();
    
    int majorVersion;
    int minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    
    windowTitleBase += std::to_string(majorVersion) + "." + std::to_string(minorVersion);
    
    FPSCounter fpsCounter;
    
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
        
        if(fpsCounter.update())
        {
            auto windowTitle = windowTitleBase + " - FPS: " + std::to_string(fpsCounter.getFPS());
            glfwSetWindowTitle(window, windowTitle.data());
        }
    }
    
    // Terminate GLFW
    glfwTerminate();
    
    // Exit program
    return EXIT_SUCCESS;
}