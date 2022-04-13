#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour) : 
    Object(pos, size, speed, colour){
        mTexture = Utils::loadTexture("src/res/textures/rock.png");
        init();
}

void Obstacle::init( void ){
    uint32_t vbo;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
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

void Obstacle::draw( void ){
    mShader->use();

    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, {mPos, 0.0f}) * glm::scale(transform, {mSize, 1.0f});

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

    mShader->setMat4("uProjection", projection);
    mShader->setMat4("uTransform", transform);
    mShader->setVec3("uColour", mColour);
    mShader->setInt("uIsBackground", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Obstacle::respawn(glm::vec2 pos){
    mPos = pos;
}
