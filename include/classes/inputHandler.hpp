#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class InputHandler
{
    public:
        InputHandler(GLFWwindow *window);
        ~InputHandler();

        void handleInput();

        bool getIsTextureApplied() const;
        glm::quat getObjectQuaternion() const;
        glm::vec3 getObjectPosition() const;
    private:
        glm::quat objectQuaternion = glm::angleAxis(float(0), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, -10.0f);
        GLFWwindow *window;
        bool isEnterPressed = false;
        bool isTextureApplied = false;
};

#endif