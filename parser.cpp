#include <classes/parser.hpp>

Parser::Parser() {
}
Parser::~Parser() {}

std::vector<DotObj*> Parser::parseFile(std::string fileName)
{
	std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error opening file : " << fileName << std::endl;
        exit(1);
    }

    std::string line;
    std::string token;
	int count = 0;
    int count2 = 0;

    objectList.clear();
    currentObject = new DotObj();
    objectList.push_back(currentObject);
    while (std::getline(file, line))
	{
        if (line[0] == '#') {
            continue ;
        }
        token = getNextToken(line, true);
        if (!token.compare("mtllib")) {
            setMTLlib(line);
        }
        else if (!token.compare("o")) {
            setObjectName(line);
        }
        else if (!token.compare("s")) {
            setSmoothingGroup(line);
        }
        else if (!token.compare("usemtl")) {
            setMaterialName(line);
        }
        else if (!token.compare("v")) {
            addVertex(line);
        }
        else if (!token.compare("f")) {
            addFace(line);
        }
        else {
            printError(line);
        }
    }
    currentObject->computeCenterMatrix();
    return (objectList);
}

void Parser::setMTLlib(std::string line) {
    std::string mtlLibName;

    mtlLibName = getNextToken(line, false);
    if (debugMode) {
        std::cout << "mtllib name : " << mtlLibName << std::endl;
    }
    //TODO download file
}

void Parser::setObjectName(std::string line) {
    std::string objectName;

    objectName = getNextToken(line, false);
    if (isFirstNameFound) {
        //currentObject = new DotObj(objectName);
        objectList.push_back(currentObject);
    }
    else {
        currentObject->setName(objectName);
        isFirstNameFound = true;
    }
    
    if (debugMode) {
        std::cout << "Object name : " << objectName << std::endl;
    }
}

void Parser::setSmoothingGroup(std::string line) {
    std::string smoothingGroup;

    smoothingGroup = getNextToken(line, false);
    if (!smoothingGroup.compare("off")) {
        if (debugMode) {
            std::cout << "Smoothing Group : " << smoothingGroup << std::endl;
        }
    }
    else {
        printError(line);
    }
}

void Parser::setMaterialName(std::string line) {
    std::string materialName;

    materialName = getNextToken(line, false);
    if (currentObject) {
        currentObject->setMaterialName(materialName);
    }
    if (debugMode) {
        std::cout << "Material name : " << materialName << std::endl;
    }
}

void Parser::addVertex(std::string line) {
    float xCoordinate;
    float yCoordinate;
    float zCoordinate;
    
    xCoordinate = std::stof(getNextToken(line, false));
    yCoordinate = std::stof(getNextToken(line, false));
    zCoordinate = std::stof(getNextToken(line, false));
    currentObject->addVertex(xCoordinate, yCoordinate, zCoordinate);
    if (debugMode) {
        std::cout << xCoordinate << " " << yCoordinate << " " << zCoordinate << " " << std::endl;
    }
}

void Parser::addFace(std::string line) {
    std::vector<u_int> indices;
    std::string token;

    while ((token = getNextToken(line, false))[0] != 'f') {
        indices.push_back(std::stoi(token) - 1);
        if (debugMode) {
            std::cout << std::stoi(token) << " ";
        }
    }
    if (debugMode) {
        std::cout << std::endl;
    }

    for (int i = 1; i < indices.size() - 1; i++) {
        currentObject->addTriangle(indices[0], indices[i], indices[i+1]);
    }
}

void Parser::printError(std::string line) {
    std::cout << "NOT SUPPORTED : " << line << std::endl;
}

std::string Parser::getNextToken(std::string line, bool shouldReset) {
    static size_t pos = std::string::npos;
    size_t startPos;
    std::string ret;

    if (shouldReset || pos == std::string::npos) {
        pos = 0;
    }
    startPos = pos;
    pos = line.find(" ", pos);
    if (pos != std::string::npos) {
        ret = line.substr(startPos, pos - startPos);
        pos++;
        return (ret);
    }
    else {
        ret = line.substr(startPos, line.size() - startPos);
        return (ret);
    }
}