#include "classes/dotObj.h"

DotObj::DotObj() : DotObj("Default name") {}

DotObj::DotObj(std::string name) : name(name) {
}

void DotObj::addVertex(float xCoordinate, float yCoordinate, float zCoordinate) {
    vertices.insert(vertices.end(), {xCoordinate, yCoordinate, zCoordinate});
}

void DotObj::addTriangle(u_int vertex1, u_int vertex2, u_int vertex3) {
    indexes.insert(indexes.end(), {vertex1, vertex2, vertex3});
}

void DotObj::setMaterialName(std::string materialName) {
    this->materialName = materialName;
}

void DotObj::setName(std::string name) {
    this->name = name;
}
std::string DotObj::getName() const {
    return name;
}

std::string DotObj::getMaterialName() const {
    return materialName;
}

float* DotObj::getVerticesData() const {
    return (float*)vertices.data();
}

std::size_t DotObj::getVerticesSize() const {
    return vertices.size() * sizeof(*vertices.data());
}

u_int* DotObj::getIndexesData() const {
    return (u_int*)indexes.data();
}

std::size_t DotObj::getIndexesSize() const {
    return indexes.size() * sizeof(*indexes.data());
}

std::ostream& operator<<(std::ostream &cout, const DotObj &obj) {
    return cout << "--------------Object Display--------------"  << std::endl
    << "Material name : " << obj.materialName << std::endl
    << "Object name : " << obj.name << std::endl
    << "------------------------------------------"  << std::endl;;
}

DotObj::~DotObj() {

}