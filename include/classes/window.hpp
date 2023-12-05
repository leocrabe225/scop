#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <interfaces/Interface_Input.hpp>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

enum class DrawMode {
    FILL,
    LINE
};

class Window : I_Input
{
    public:
        Window(const char *name, DrawMode drawMode);
        ~Window();

        GLFWwindow *getWindow() const;
        int ShouldContinue();
        void Clear();
        void SwapBuffersAndPollEvents();
		void SendKeys(u_char *keyState) override;
    private:
        GLFWwindow *window;
};

#endif