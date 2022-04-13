#include "Ball.h"

Ball::Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour) : 
    Object(pos, size, speed, colour){
        mIsMoving = false;
        mTexture = Utils::loadTexture("src/res/textures/rock.png");
        init();
}

void Ball::init( void ){
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

    calculateMovement();
    
}

void Ball::update(float dt, GLFWwindow* contextID){
    if(glfwGetKey(contextID, GLFW_KEY_SPACE) == GLFW_PRESS){
        mIsMoving = true;
    }

    if(mIsMoving){
        mPos += (mSpeedFactor * dt);
    }
}

void Ball::draw( void ){
    mShader->use();

    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, {mPos, 0.0f}) * glm::scale(transform, {mSize, 0.0f});
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

    mShader->setMat4("uProjection", projection);
    mShader->setMat4("uTransform", transform);
    mShader->setVec3("uColour", mColour);
    mShader->setInt("uIsBackground", 1);

    glBindVertexArray(mVao);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Ball::calculateMovement( void ){
    mMoveDir = Utils::random(-10, 10);

    if(mMoveDir < 0){
        mMoveAngle = Utils::random(glm::radians(150.0f), glm::radians(210.0f));
        mSpeedFactor.x = mSpeed.x * -glm::cos(mMoveAngle);
        mSpeedFactor.y = mSpeed.y * -glm::sin(mMoveAngle);
        
    }
    else{
        mMoveAngle = Utils::random(glm::radians(30.0f), glm::radians(330.0f));
        mSpeedFactor.x = mSpeed.x * glm::cos(mMoveAngle);
        mSpeedFactor.y = mSpeed.y * glm::sin(mMoveAngle);
    }
    mSpeedCap = mSpeedFactor.x * 3.0f;
}


void Ball::respawn( glm::vec2 pos ){
    mColour = {0.0f, 1.0f, 0.0f};
    mPos = pos;
    mIsMoving = false;
    calculateMovement();
}

bool Ball::onCollideWalls( void ){
    bool result = false;

    if(mPos.y <= 0.0f){
        mSpeedFactor.y *= -1;
        mPos.y = 0.0f;
        result = true;
    }

    if(mPos.y + mSize.y >= SCREEN_HEIGHT){
        mSpeedFactor.y *= -1;
        mPos.y = SCREEN_HEIGHT - mSize.y;
        result = true;
    }
    return result;
}

bool Ball::onCollideObject(Object* object){
    bool collideX = mPos.x + mSize.x >= object->getPos()->x && object->getPos()->x + object->getSize()->x >= mPos.x;
    bool collideY = mPos.y + mSize.y >= object->getPos()->y && object->getPos()->y + object->getSize()->y >= mPos.y;

    bool result = collideX && collideY;

    if(result){
        if(abs(mSpeedFactor.x) <= abs(mSpeedCap)){
            mSpeedFactor.x *= -1.1;
        }
        else{
            mSpeedFactor.x *= -1;
        }
    }
    return result;
}

bool Ball::outOfBoundLeft( void ){
    return mPos.x <= 0.0f;
}

bool Ball::outOfBoundsRight( void ){
    return mPos.x + mSize.x >= SCREEN_WIDTH;
}

void Ball::setColour( glm::vec3 colour ){
    mColour = colour;
}


