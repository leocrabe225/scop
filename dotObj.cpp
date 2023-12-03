#include <classes/dotObj.hpp>

DotObj::DotObj() : DotObj("Default name") {}

DotObj::DotObj(std::string name) : name(name) {
}

void DotObj::addVertex(float xCoordinate, float yCoordinate, float zCoordinate) {
    vertices.insert(vertices.end(), {xCoordinate, yCoordinate, zCoordinate});
}

void DotObj::addTriangle(u_int vertex1, u_int vertex2, u_int vertex3) {
    indexes.insert(indexes.end(), {vertex1, vertex2, vertex3});
}

void DotObj::computeCenterMatrix() {
    float minX = FLT_MAX;
    float maxX = FLT_MIN;
    float minY = FLT_MAX;
    float maxY = FLT_MIN;
    float minZ = FLT_MAX;
    float maxZ = FLT_MIN;

    int i = 0;
    for (std::vector<float>::iterator iterator = vertices.begin(); iterator != vertices.end(); iterator++) {
        if (i == 0) {
            if (*iterator < minX) {
                minX = *iterator;
            }
            else if (*iterator > maxX) {
                maxX = *iterator;
            }
        }
        else if (i == 1) {
            if (*iterator < minY) {
                minY = *iterator;
            }
            else if (*iterator > maxY) {
                maxY = *iterator;
            }
        }
        else {
            if (*iterator < minZ) {
                minZ = *iterator;
            }
            else if (*iterator > maxZ) {
                maxZ = *iterator;
            }
        }
        i = (i + 1) % 3;
    }
    if (debugMode) {
        std::cout << -(minX + maxX) / 2 << " " << -(minY + maxY) / 2 << " " << -(minZ + maxZ) / 2 << std::endl;
    }
    centerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(minX + maxX) / 2, -(minY + maxY) / 2, -(minZ + maxZ) / 2));
    if (textureOn) {
        //computeTextureCoords();
        UVunwrapping(glm::vec3(minX,minY,minZ), glm::vec3(maxX,maxY,maxZ));
    }
}

void DotObj::UVunwrapping(glm::vec3 minBounds, glm::vec3 maxBounds) {
    float ratio = 15;
    glm::vec3 center = 0.5f * (minBounds + maxBounds);
    glm::vec3 extents = 0.5f * (maxBounds - minBounds);
    // Compute UV coordinates based on planar mapping
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glm::vec3 vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 localPos = vertex - center;

        float u = (atan2(localPos.z, localPos.x) + glm::pi<float>()) / (2.0f * glm::pi<float>());
        float v = (asin(localPos.y / extents.y) + glm::half_pi<float>()) / glm::pi<float>();

        // Store the UV coordinates in your DotObj data
        // Assuming vertices have XYZ coordinates
        texturedVertices.insert(texturedVertices.end(), {vertices[i], vertices[i+1], vertices[i+2], u * ratio, v * ratio});
    }
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

std::vector<float> DotObj::getVertices(VertexType type) const {
    if (type == VertexType::TEXTURED) {
        return texturedVertices;
    }
    else {
        return vertices;
    }
}

std::vector<u_int> DotObj::getIndexes() const {
    return indexes;
}

float* DotObj::getVerticesData(VertexType type) const {
    if (type == VertexType::TEXTURED) {
        return (float*)texturedVertices.data();
    }
    else {
        return (float*)vertices.data();
    }
}

std::size_t DotObj::getVerticesSize(VertexType type) const {
    if (type == VertexType::TEXTURED) {
        return texturedVertices.size() * sizeof(*texturedVertices.data());
    }
    else {
        return vertices.size() * sizeof(*vertices.data());
    }
}

u_int* DotObj::getIndexesData() const {
    return (u_int*)indexes.data();
}

std::size_t DotObj::getIndexesSize() const {
    return indexes.size() * sizeof(*indexes.data());
}

glm::mat4 DotObj::getCenterMatrix() const {
    return centerMatrix;
}

std::ostream& operator<<(std::ostream &cout, const DotObj &obj) {
    return cout << "--------------Object Display--------------"  << std::endl
    << "Material name : " << obj.materialName << std::endl
    << "Object name : " << obj.name << std::endl
    << "------------------------------------------"  << std::endl;;
}

DotObj::~DotObj() {

}