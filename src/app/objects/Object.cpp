#include "Object.h"

Object::Object(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour){
    mPos = pos;
    mSize = size;
    mSpeed = speed;
    mColour = colour;
    mShader = Utils::createShader("src/shaders/mainShader.txt");
}


glm::vec2* Object::getPos( void ){
    return &mPos;
}

glm::vec2* Object::getSize( void ){
    return &mSize;
}

glm::vec2* Object::getSpeed( void ){
    return &mSpeed;
}

glm::vec3* Object::getColour( void ){
    return &mColour;
}

Shader* Object::getShader( void ){
    return mShader;
}

uint32_t Object::getVao( void ){
    return mVao;
}

uint32_t Object::getTexture( void ){
    return mTexture;
}

void Object::setPos(glm::vec2 pos){
    mPos = pos;
}

void Object::setSize(glm::vec2 size){
    mSize = size;
}

void Object::setSpeed(glm::vec2 speed){
    mSpeed = speed;
}

void Object::setColour(glm::vec3 colour){
    mColour = colour;
}

