#include <classes/vertexArrayObject.hpp>

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &VAO);
    bind();
}

VertexArrayObject::VertexArrayObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) : VertexArrayObject()  {
    setupVBO(vertices);
    EBO = new ElementArrayBuffer(indices);
}

VertexArrayObject::VertexArrayObject(ElementArrayBuffer *EBO, const std::vector<float>& vertices) : VertexArrayObject() {
    this->EBO = EBO;
    EBO->Bind();
    setupVBO(vertices);
}

VertexArrayObject::VertexArrayObject(unsigned int VBO, const std::vector<unsigned int>& indices) : VertexArrayObject() {
    this->VBO = VBO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    EBO = new ElementArrayBuffer(indices);
}

VertexArrayObject::VertexArrayObject(unsigned int VBO, ElementArrayBuffer *EBO) : VertexArrayObject() {
    this->VBO = VBO;
    this->EBO = EBO;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    EBO->Bind();
}

void VertexArrayObject::setupVBO(const std::vector<float>& vertices) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    std::cout << "VBO " << vertices.size() * sizeof(float) << " " << vertices.data() << std::endl;
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

unsigned int VertexArrayObject::GetVAO() {
    return VAO;
}

unsigned int VertexArrayObject::GetVBO() {
    return VBO;
}

ElementArrayBuffer *VertexArrayObject::GetEBO() {
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
    EBO->DeleteBuffers();
}