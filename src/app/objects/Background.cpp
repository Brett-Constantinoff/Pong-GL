#include "Background.h"

Background::Background(glm::vec2 size, glm::vec2 position){
    mShader = Utils::createShader("src/shaders/mainShader.txt");
    mTextureID = Utils::loadTexture("src/res/textures/background.png");
    mSize = size;
    mPos = position;
    init();
}

void Background::init( void ){  
    uint32_t vbo;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    mVao = Utils::genVertexArray();
    vbo = Utils::genBuffer();
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(mVao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

void Background::draw( void ){
    mShader->use();

    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, {mPos, 0.0f}) * glm::scale(transform, {mSize, 0.0f});
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

    mShader->setMat4("uProjection", projection);
    mShader->setMat4("uTransform", transform);
    mShader->setInt("uIsBackground", 0);

    glBindVertexArray(mVao);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Shader* Background::getShader( void ){
    return mShader;
}

uint32_t Background::getTexture( void ){
    return mTextureID;
}
