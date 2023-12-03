#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <classes/texture.hpp>
#include <stb/stb_image.h>

class TextureLoader
{
    public:
        TextureLoader();
        ~TextureLoader();

        Texture loadTexture(std::string fileName);
};

#endif