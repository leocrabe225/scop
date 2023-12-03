#include <classes/window.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //callback called by GLFW whevenever window is resized
{
    glViewport(0, 0, width, height); // We tell openGL the new size of the window
}

Window::Window(const char *name, DrawMode drawMode) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  //OpenGL version ->4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //OpenGL version   4.3<-
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We use the core profile because we want to use the modulable part of OpenGL

    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, name, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window); // Set active context to the window we created

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Load OpenGL function pointers with GLFW OS pointer
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT); // Tell OpenGL the size of the drawing window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Sets clear color
    if (drawMode == DrawMode::LINE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw as lines
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default draw (filled)
    }
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // We tell glfw which function to call whenever window is resized
}

Window::~Window() {}

GLFWwindow *Window::getWindow() const {
    return window;
}