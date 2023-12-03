#ifndef PARSER_H
#define PARSER_H
  
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <classes/dotObj.hpp>
  

class Parser
{ 
    public : 
        Parser();
        ~Parser();
        std::vector<DotObj*> parseFile(std::string fileName);

    private :
        std::vector<DotObj*> objectList;
        DotObj *currentObject = NULL;
        bool debugMode = false;
        bool isFirstNameFound = false;

        

        void setMTLlib(std::string line);
        void setObjectName(std::string line);
        void setSmoothingGroup(std::string line);
        void setMaterialName(std::string line);
        void addVertex(std::string line);
        void addFace(std::string line);


        std::string getNextToken(std::string line, bool shouldReset);
        void printError(std::string type);
};
  
#endif