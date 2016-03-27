
#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <GLFW/glfw3.h>

#include <chrono>

class FPSCounter
{
public:
    FPSCounter() :
        m_RefreshRate(500),
        m_CurrentTime(0),
        m_FrameTime(0)
    {
    }
    
    void startFrame()
    {
        auto now = std::chrono::system_clock::now();
        auto nowMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        
    }
    
    bool update()
    {
        m_FrameCount++;
        
        if(m_CurrentTime > m_RefreshRate)
        {
            auto currentFPS = m_FrameCount / std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrentTime).count();
            
            std::cout << currentFPS << std::endl;
            
            m_CurrentTime = std::chrono::milliseconds(0);
            m_FrameCount = 0;
            
            return true;
        }
        
        return false;
    }
    
private:
    std::chrono::milliseconds m_RefreshRate;
    std::chrono::milliseconds m_CurrentTime;
    std::chrono::milliseconds m_FrameTime;
    int                       m_FrameCount    = 0;
};

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
    int width, height;
    
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
        
        fpsCounter.update();
    }
    
    // Terminate GLFW
    glfwTerminate();
    
    // Exit program
    exit( EXIT_SUCCESS );
}