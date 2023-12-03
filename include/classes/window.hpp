#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

enum class DrawMode {
    FILL,
    LINE
};

class Window
{
    public:
        Window(const char *name, DrawMode drawMode);
        ~Window();
        GLFWwindow *getWindow() const;
    private:
        GLFWwindow *window;
};

#endif