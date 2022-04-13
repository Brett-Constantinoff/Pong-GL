#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "../../shaders/Shader.h"
#include "../../utils/Utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>


class Player : public Object{
    public:
        Player(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour, std::string moveMode);
        void init( void );
        void update(float dt, GLFWwindow* contextID, glm::vec2 bounds);
        void draw( void );
    
    private:
        std::string mMoveMode;
};
#endif