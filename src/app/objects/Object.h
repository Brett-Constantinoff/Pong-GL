#ifndef OBJECT_H
#define OBJECT_H

#include "../../shaders/Shader.h"
#include "../../utils/Utils.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Object{
    
    public:
        Object(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour);
        glm::vec2* getSize( void );
        glm::vec2* getPos( void );
        glm::vec2* getSpeed( void );
        glm::vec3* getColour( void );
        Shader* getShader(void);
        uint32_t getVao( void );
        uint32_t getTexture( void );
        void setSize( glm::vec2 size);
        void setPos( glm::vec2 pos);
        void setSpeed( glm::vec2 speed);
        void setColour( glm::vec3 colour);


    protected:
        glm::vec2 mPos;
        glm::vec2 mSize;
        glm::vec2 mSpeed;
        glm::vec3 mColour;
        Shader* mShader;
        uint32_t mVao;
        uint32_t mTexture;
};

#endif