#include <main.hpp>

int main(int argc, char **argv) {
    if (argc < 2) {
        return (1);
    }
    Parser *parser = new Parser();
    std::vector<DotObj*> objectList = parser->parseFile(argv[1]);
    if (objectList.size() == 0) {
        return (1);
    }

    Window *window = new Window(objectList[0]->getName().c_str(), DrawMode::FILL);

    InputHandler *inputHandler = new InputHandler(window->getWindow());

    TextureLoader *textureLoader = new TextureLoader();
    Texture texture = textureLoader->loadTexture("../resources/wall.jpg");

    Shader *shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader->use();

    VertexArrayObject *VAO_1 = new VertexArrayObject(objectList[0]->getVertices(VertexType::TEXTURED), objectList[0]->getIndexes());
    VAO_1->addVertexAttribute(0,3,GL_FLOAT);
    VAO_1->addVertexAttribute(1,2,GL_FLOAT);

    VertexArrayObject *VAO_2 = new VertexArrayObject(VAO_1->getEBO(), objectList[0]->getVertices(VertexType::DEFAULT));
    VAO_2->addVertexAttribute(0,3,GL_FLOAT);

    VertexArrayObject *activeVAO = VAO_2;
    while(!glfwWindowShouldClose(window->getWindow())) //If window has not been instructed to close, continue
    {
        inputHandler->handleInput();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Clears window with set clear color
        if (inputHandler->getIsTextureApplied()) {
            if (activeVAO != VAO_1) {
                VAO_2->unbind();
                VAO_1->bind();
                activeVAO = VAO_1;
            }
        }
        else if (activeVAO != VAO_2) {
            VAO_1->unbind();
            VAO_2->bind();
            activeVAO = VAO_2;
        }

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)DEFAULT_WINDOW_WIDTH/(float)DEFAULT_WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = proj * glm::translate(matrix, inputHandler->getObjectPosition()) * glm::toMat4(inputHandler->getObjectQuaternion()) * objectList[0]->getCenterMatrix();
        shader->setmat4("proj", matrix);

        glDrawElements(GL_TRIANGLES, objectList[0]->getIndexesSize(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window->getWindow()); //Swaps Window buffers to avoid flickering
        glfwPollEvents(); //Checks for event and calls callbacks (framebuffer_size_callback wouldn't be called if it wasn't for this function)
    }

    glfwTerminate(); // clean/delete GLFW resources that were allocated
    return 0;
}