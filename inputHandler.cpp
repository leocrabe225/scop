#include <classes/inputHandler.hpp>

const float speed = 0.05f;
const float rotationSpeed = 0.01f;

InputHandler::InputHandler(GLFWwindow *window) : window(window) {}

void InputHandler::handleInput()
{
    static bool isPressed = false;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if Escape key is pressed
        glfwSetWindowShouldClose(window, true); // Tell GLFW that window should close (The loop will close)

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, 0, -speed);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, 0, speed);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(speed, 0, 0);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(-speed, 0, 0);

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, speed, 0);

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, -speed, 0);

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){ // Check if Escape key is pressed
        if (!isPressed) {
            isTextureApplied = !isTextureApplied;
            isPressed = true;
        }
    }   
    else  {
        isPressed = false;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }  

    if(glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-rotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }
}

bool InputHandler::getIsTextureApplied() const {
    return isTextureApplied;
}

// Getter for objectQuaternion
glm::quat InputHandler::getObjectQuaternion() const {
    return objectQuaternion;
}

// Getter for objectPosition
glm::vec3 InputHandler::getObjectPosition() const {
    return objectPosition;
}

InputHandler::~InputHandler() {}