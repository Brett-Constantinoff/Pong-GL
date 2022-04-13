#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Object.h"
#include "../../utils/Utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <limits>
#include <vector>

class Obstacle : public Object{
    public:
        Obstacle(glm::vec2 pos, glm::vec2 size, glm::vec2 speed, glm::vec3 colour);
        void init( void );
        void update(void);
        void draw( void );
        void respawn(glm::vec2 pos);
};
#endif