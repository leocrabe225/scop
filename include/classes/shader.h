#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{
    public:
    unsigned int ID; // the program ID
  
    Shader(const char* vertexPath, const char* fragmentPath); // constructor reads and builds the shader
    void use();// use/activate the shader

    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};
  
#endif