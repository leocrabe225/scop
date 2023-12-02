#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <classes/shader.h>
#include <classes/parser.h>

#include <iostream>
#include <math.h>

#include <ctime>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //callback called by GLFW whevenever window is resized
{
    glViewport(0, 0, width, height); // We tell openGL the new size of the window
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if Escape key is pressed
        glfwSetWindowShouldClose(window, true); // Tell GLFW that window should close (The loop will close)
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

    //std::cout << "Project is alive" << std::endl;

    Shader *shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader->use();

    glEnable(GL_DEPTH_TEST);  

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::srand(std::time(nullptr));

    float offset  = 0.0f;
    /*float *vertices = new float[48];
    for (int z = 0; z < 2; z++) {
        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 2; x++) {
                vertices[(z * 2 * 2 + y * 2 + x) * 6] = -0.5f + (float)x;
                vertices[(z * 2 * 2 + y * 2 + x) * 6 + 1] = -0.5f + (float)y;
                vertices[(z * 2 * 2 + y * 2 + x) * 6 + 2] = -0.5f + (float)z;
                vertices[(z * 2 * 2 + y * 2 + x) * 6 + 3] = (float)(std::rand() % 256) / 256;
                vertices[(z * 2 * 2 + y * 2 + x) * 6 + 4] = (float)(std::rand() % 256) / 256;
                vertices[(z * 2 * 2 + y * 2 + x) * 6 + 5] = (float)(std::rand() % 256) / 256;
                }
        }
    }*/
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // front top right
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        0.5f, -0.5f, 0.0f,  // front bottom right
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        -0.5f, -0.5f, 0.0f,  // front bottom left
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        -0.5f,  0.5f, 0.0f,   // front top left
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        0.5f,  0.5f, 1.0f,  // back top right
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        0.5f, -0.5f, 1.0f,  // back bottom right
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        -0.5f, -0.5f, 1.0f,  // back bottom left
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
        -0.5f,  0.5f, 1.0f, // back top left
        (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256, (float)(std::rand() % 256) / 256,
    };
    /*for (int i = 0; i < 48; i += 6) {
        std::cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2]<< std::endl;
        std::cout << vertices[i+3] << " " << vertices[i+4] << " " << vertices[i+5] << std::endl << std::endl;
    }
    std::cout  << (float)(std::rand() % 256) / 256 << " " << (float)(std::rand() % 256) / 256 << " " << (float)(std::rand() % 256) / 256  << std::endl;*/
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3 ,   // second triangle
        0,1,4,
        1,4,5,
        2,3,7,
        2,6,7,
        4,5,6,
        4,6,7,
        1,2,5,
        2,5,6,
        0,3,4,
        3,4,7
    };
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

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)DEFAULT_WINDOW_WIDTH/(float)DEFAULT_WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = proj * glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
    
    float rand1 = (float)(std::rand() % 100) / 100;
    float rand2 = (float)(std::rand() % 100) / 100;
    float rand3 = (float)(std::rand() % 100) / 100;
    float normalize = (rand1 * rand1 + rand2 * rand2 + rand3 * rand3);
    rand1 /= normalize;
    rand2 /= normalize;
    rand3 /= normalize;
    
    float angle = 0;

    while(!glfwWindowShouldClose(window)) //If window has not been instructed to close, continue
    {
        angle += 0.5f;
        processInput(window);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clears window with set clear color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue * 3) / 2.0f + 0.5f;
        float redValue = sin(timeValue * 2) / 2.0f + 0.5f;
        float blueValue = sin(timeValue * 1) / 2.0f + 0.5f;
        shader->setFloat4("ourColor", redValue, greenValue, blueValue, 1.0f);
        glm::mat4 view2 = glm::rotate(view, glm::radians(angle), glm::vec3(rand1, rand2, rand3));
        shader->setmat4("proj", view2);
        glDrawElements(GL_TRIANGLES, objectList[0]->getIndexesSize(), GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); //Swaps Window buffers to avoid flickering
        glfwPollEvents(); //Checks for event and calls callbacks (framebuffer_size_callback wouldn't be called if it wasn't for this function)
    }

    glfwTerminate(); // clean/delete GLFW resources that were allocated
    return 0;
}