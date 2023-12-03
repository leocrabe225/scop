#ifndef DOTOBJ_H
#define DOTOBJ_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
  
enum class VertexType {
    DEFAULT,
    TEXTURED,
    // Add more mapping types as needed
};

class DotObj
{ 
    public : 
        DotObj();
        DotObj(std::string name);

        void setName(std::string name);
        std::string getName() const;
        std::string getMaterialName() const;
        std::vector<float> getVertices(VertexType type) const;
        std::vector<u_int> getIndexes() const;

        float* getVerticesData(VertexType) const;
        std::size_t getVerticesSize(VertexType) const;
        u_int* getIndexesData() const;
        std::size_t getIndexesSize() const;
        glm::mat4 getCenterMatrix() const;

        void addVertex(float xCoordinate, float yCoordinate, float zCoordinate);
        void addTriangle(u_int vertex1, u_int vertex2, u_int vertex3);
        void computeCenterMatrix();
        
        void setMaterialName(std::string materialName);
    private :
        std::vector<float> vertices;
        std::vector<float> texturedVertices;
        std::vector<u_int> indexes;
        glm::mat4 centerMatrix;
        std::string name;
        std::string materialName;
        bool debugMode = true;
        bool textureOn = true;

        void computeTextureCoords();
        void UVunwrapping(glm::vec3 minBounds, glm::vec3 maxBounds);
        ~DotObj();
    friend std::ostream& operator<<(std::ostream& os, const DotObj& obj);
};

#endif