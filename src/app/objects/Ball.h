#ifndef BALL_H
#define BALL_H

#include "../../shaders/Shader.h"
#include "../../utils/Utils.h"
#include "Object.h"
#include "Player.h"
#include "Obstacle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

class Ball : public Object{
    public:
        Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour);
        void init( void );
        void update(float dt, GLFWwindow* contextID);
        void draw( void );
        void respawn(glm::vec2 pos);
        bool outOfBoundLeft( void );
        bool outOfBoundsRight( void );
        bool onCollideWalls( void );
        bool onCollideObject( Object* player );
        void setColour( glm::vec3 colour );

    private:
        void calculateMovement( void );

    private:
        float mSpeedCap;
        bool mIsMoving;
        int mMoveDir;
        float mMoveAngle;
        glm::vec2 mSpeedFactor;
};
#endif