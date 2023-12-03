#pragma once

#include <glad/glad.h>
#include <vector>
#include <classes/dotObj.hpp>

class VertexArrayObject {
public:
    VertexArrayObject(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    VertexArrayObject(unsigned int EBO, const std::vector<float>& vertices);
    VertexArrayObject(unsigned int VBO, const std::vector<unsigned int>& indices);
    VertexArrayObject(unsigned int VBO, unsigned int EBO);
    ~VertexArrayObject();

    void addVertexAttribute(u_int location, u_int size, GLenum type);

    void bind();
    void unbind();
    unsigned int getVBO();
    unsigned int getEBO();
private:
    VertexArrayObject();
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    std::vector<glm::uvec2> locationList;
    int totalStride = 0;

    void setupVBO(const std::vector<float>& vertices);
    void setupEBO(const std::vector<unsigned int>& indices);
    
};