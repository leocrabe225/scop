#ifndef DOTOBJ_H
#define DOTOBJ_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
  

class DotObj
{ 
    public : 
        DotObj();
        DotObj(std::string name);

        void setName(std::string name);
        std::string getName() const;
        std::string getMaterialName() const;

        float* getVerticesData() const;
        std::size_t getVerticesSize() const;
        u_int* getIndexesData() const;
        std::size_t getIndexesSize() const;
        glm::mat4 getCenterMatrix() const;

        void addVertex(float xCoordinate, float yCoordinate, float zCoordinate);
        void addTriangle(u_int vertex1, u_int vertex2, u_int vertex3);
        void computeCenterMatrix();
        void setMaterialName(std::string materialName);
    private :
        std::vector<float> vertices;
        std::vector<u_int> indexes;
        glm::mat4 centerMatrix;
        std::string name;
        std::string materialName;
        bool debugMode = true;

        ~DotObj();
    friend std::ostream& operator<<(std::ostream& os, const DotObj& obj);
};

#endif