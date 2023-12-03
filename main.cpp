#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <classes/shader.h>
#include <classes/parser.h>

#include <iomanip>
#include <iostream>
#include <math.h>

#include <ctime>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

void printMat4(const glm::mat4& matrix, int precision = 6) {
    const float* matData = glm::value_ptr(matrix);

    std::cout << "Matrix 4x4:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Set precision for floating-point output
            std::cout << std::fixed << std::setw(precision + 5) << std::setprecision(precision) << matData[i * 4 + j] << "\t";
        }
        std::cout << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //callback called by GLFW whevenever window is resized
{
    glViewport(0, 0, width, height); // We tell openGL the new size of the window
}

glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, -10.0f);
glm::mat4 objectRotation = glm::mat4(1);
glm::quat objectQuaternion = glm::angleAxis(float(0), glm::vec3(0.0f, 0.0f, 1.0f));;

void processInput(GLFWwindow *window)
{
    const float objectSpeed = 0.05f;
    const float objectRotationSpeed = 0.01f;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if Escape key is pressed
        glfwSetWindowShouldClose(window, true); // Tell GLFW that window should close (The loop will close)

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, 0, -objectSpeed);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, 0, objectSpeed);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(objectSpeed, 0, 0);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(-objectSpeed, 0, 0);

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, objectSpeed, 0);

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) // Check if Escape key is pressed
        objectPosition += glm::vec3(0, -objectSpeed, 0);



    if(glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-objectRotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(objectRotationSpeed, glm::vec3(1.0f, 0.0f, 0.0f)) * objectQuaternion;
    }  

    if(glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-objectRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(objectRotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(objectRotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }

    if(glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS) {
        objectQuaternion = glm::angleAxis(-objectRotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f)) * objectQuaternion;
    }

    objectRotation = glm::toMat4(objectQuaternion);

    printMat4(objectRotation);

}

int main(int argc, char **argv) {
    if (argc < 2) {
        return (1);
    }
    Parser *parser = new Parser();
    std::vector<DotObj*> objectList = parser->parseFile(argv[1]);
    if (objectList.size() == 0) {
        return (1);
    }
    std::cout << objectList[0]->getVerticesSize() << " " << objectList[0]->getIndexesSize() <<  std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  //OpenGL version ->4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //OpenGL version   4.3<-
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We use the core profile because we want to use the modulable part of OpenGL

    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, objectList[0]->getName().c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Set active context to the window we created

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Load OpenGL function pointers with GLFW OS pointer
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT); // Tell OpenGL the size of the drawing window
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // We tell glfw which function to call whenever window is resized


    Shader *shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader->use();

    glEnable(GL_DEPTH_TEST);  

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::srand(std::time(nullptr));

    unsigned int VBO; // Vertex buffer objects
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, objectList[0]->getVerticesSize(), objectList[0]->getVerticesData(), GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, objectList[0]->getIndexesSize(), objectList[0]->getIndexesData(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    //glEnableVertexAttribArray(1);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Sets clear color
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw as lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // default draw (filled)

    
    
    float rand1 = (float)(std::rand() % 100) / 100;
    float rand2 = (float)(std::rand() % 100) / 100;
    float rand3 = (float)(std::rand() % 100) / 100;
    float normalize = (rand1 * rand1 + rand2 * rand2 + rand3 * rand3);
    rand1 /= normalize;
    rand2 /= normalize;
    rand3 /= normalize;

    while(!glfwWindowShouldClose(window)) //If window has not been instructed to close, continue
    {
        //angle += 0.01f;
        processInput(window);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clears window with set clear color
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)DEFAULT_WINDOW_WIDTH/(float)DEFAULT_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = proj * glm::translate(matrix, objectPosition) * objectRotation * objectList[0]->getCenterMatrix();
    
        shader->setmat4("proj", matrix);
        glDrawElements(GL_TRIANGLES, objectList[0]->getIndexesSize(), GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); //Swaps Window buffers to avoid flickering
        glfwPollEvents(); //Checks for event and calls callbacks (framebuffer_size_callback wouldn't be called if it wasn't for this function)
    }

    glfwTerminate(); // clean/delete GLFW resources that were allocated
    return 0;
}