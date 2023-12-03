#include <classes/textureLoader.hpp>  // Make sure to include the corresponding header file

TextureLoader::TextureLoader() {
    if (!glfwGetCurrentContext()) {
        std::cout << "TextureLoader cannot be used before a glfw context has been initialized" << std::endl;
        exit(1);
    }
    stbi_set_flip_vertically_on_load(true);
}

TextureLoader::~TextureLoader() {
    // Destructor implementation, if needed
}

Texture TextureLoader::loadTexture(std::string fileName) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        return Texture(textureID, width, height, nrChannels);
    } else {
        std::cout << "Failed to load texture : " << fileName << std::endl;
        exit(1);
    }
}