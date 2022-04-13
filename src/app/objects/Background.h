#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../shaders/Shader.h"
#include "../../utils/Utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>


class Background{
    public:
        Background(glm::vec2 size, glm::vec2 position);
        void draw( void );
        Shader* getShader(void);
        uint32_t getTexture( void );

    private:
        uint32_t mTextureID;
        uint32_t mVao;
        Shader* mShader;
        glm::vec2 mSize;
        glm::vec2 mPos;

    private:
        void init( void );

};
#endif