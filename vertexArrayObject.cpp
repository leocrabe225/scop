#include <classes/vertexArrayObject.hpp>

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &VAO);
    bind();
}

VertexArrayObject::VertexArrayObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : VertexArrayObject()  {
    setupVBO(vertices);
    setupEBO(indices);
}

VertexArrayObject::VertexArrayObject(unsigned int EBO, const std::vector<float>& vertices) : VertexArrayObject() {
    this->EBO = EBO;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    setupVBO(vertices);
}

VertexArrayObject::VertexArrayObject(unsigned int VBO, const std::vector<unsigned int>& indices) : VertexArrayObject() {
    this->VBO = VBO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    setupEBO(indices);
}

VertexArrayObject::VertexArrayObject(unsigned int VBO, unsigned int EBO) : VertexArrayObject() {
    this->VBO = VBO;
    this->EBO = EBO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void VertexArrayObject::setupVBO(const std::vector<float>& vertices) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    std::cout << "VBO " << vertices.size() * sizeof(float) << " " << vertices.data() << std::endl;
}

void VertexArrayObject::setupEBO(const std::vector<unsigned int>& indices) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    std::cout << "EBO " << indices.size() * sizeof(float) << " " << indices.data() << std::endl;
}

void VertexArrayObject::addVertexAttribute(u_int location, u_int size, GLenum type) {
    locationList.push_back(glm::uvec2(location, size));
    GLsizei offset = totalStride;
    totalStride += size * sizeof(type);
    
    int tempStride = 0;
    for (std::vector<glm::uvec2>::iterator iterator = locationList.begin(); iterator != locationList.end(); iterator++) {
        glVertexAttribPointer(iterator->x, iterator->y, type, GL_FALSE, totalStride, (void*)tempStride);
        tempStride += iterator->y * 4;
    }
    glEnableVertexAttribArray(location);
}

unsigned int VertexArrayObject::getVBO() {
    return VBO;
}

unsigned int VertexArrayObject::getEBO() {
    return EBO;
}

void VertexArrayObject::bind() {
    glBindVertexArray(VAO);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
    for (std::vector<glm::uvec2>::iterator iterator = locationList.begin(); iterator != locationList.end(); iterator++) {
        glDisableVertexAttribArray(iterator->x);
    }
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}