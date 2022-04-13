#include "Utils.h"
#include "../libs/stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>

std::vector<unsigned int> Utils::mVaos; //vertex arrays
std::vector<unsigned int> Utils::mVbos; //vertex buffers
std::vector<unsigned int> Utils::mTbos; //texture buffers
std::vector<unsigned int> Utils::mPrograms; //shader programs
std::vector<Shader*> Utils::mShaders; //shaders


//creates a shader object given a glsl shader file
Shader* Utils::createShader(std::string fileName){
    Shader* shader = new Shader(fileName);
    mShaders.push_back(shader);
    mPrograms.push_back(shader->getId());
    return shader;
}

//generates a texture ID
uint32_t Utils::genTexture( void ){
    uint32_t textureID;
    glGenTextures(1, &textureID);
    mTbos.push_back(textureID);
    return textureID;
}

//creates a new buffer ID
uint32_t Utils::genBuffer( void ){
    uint32_t bufferID;
    glGenBuffers(1, &bufferID);
    mVbos.push_back(bufferID);
    return bufferID;
}

//creates a new vao ID
uint32_t Utils::genVertexArray( void ){
    uint32_t vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    mVaos.push_back(vertexArrayID);
    return vertexArrayID;
}

//loads a cube map and returns its ID
uint32_t Utils::loadCubeMap( std::vector<std::string> mapFiles ){

    uint32_t textureID = genTexture();
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width;
    int height;
    int channels;
    for(int i = 0; i < mapFiles.size(); i++){
        uint8_t* fileData = stbi_load(mapFiles[i].c_str(), &width, &height, &channels, 0);
        if(fileData){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, fileData);
        }
        else{
            std::cout << "File failed to load: " << mapFiles[i] << std::endl;
        }
        stbi_image_free(fileData);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    mTbos.push_back(textureID);
    return textureID;
}

//loads a texture and returns its ID
uint32_t Utils::loadTexture(std::string fileName){
    uint32_t textureID = genTexture();
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width;
    int height;
    int channels;
  
    unsigned char* fileData = stbi_load(fileName.c_str(), &width, &height, &channels, 0);
    if(fileData){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, fileData);
    }
    else{
        std::cout << "File failed to load: " << fileName << std::endl;
    }
    stbi_image_free(fileData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    mTbos.push_back(textureID);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

//creates a new sound engine
irrklang::ISoundEngine* Utils::createSoundEngine( void ){
    irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
    if(!soundEngine){
        std::cout << "ERROR INIT SOUND ENGINE" << std::endl;
        exit(EXIT_FAILURE);
    }
    return soundEngine;
}

//delete app resources
void Utils::deleteResources( void ){
    for(auto vao : mVaos){
        glDeleteVertexArrays(1, &vao);
    }
    for (auto vbo: mVbos){
        glDeleteBuffers(1, &vbo);
    }
    for (auto tbo: mTbos){
        glDeleteTextures(1, &tbo);
    }
    for (auto p : mPrograms){
        glDeleteProgram(p);
    }
    for(auto shader: mShaders){
        delete shader;
    }
}
