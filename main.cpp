
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <GLFW/glfw3.h>

void draw()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
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
}

int main()
{
    GLFWwindow* window;
    int width, height;
    
    if( !glfwInit() )
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fprintf( stderr, "Failed to initialize GLFW\n" );
        
    }
    
    glbinding::Binding::initialize();
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow( 800, 600, "Physically Based Rendering with OpenGL", NULL, NULL );
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
    
    // Parse command-line options
    init();
    
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
    }
    
    // Terminate GLFW
    glfwTerminate();
    
    // Exit program
    exit( EXIT_SUCCESS );
}