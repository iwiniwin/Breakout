#ifndef COLLISION_DETECT_H
#define COLLISION_DETECT_H


#include "glm.hpp"

class CollisionDetect
{
private:
    CollisionDetect() {};
public:
    static bool CheckAABB(glm::vec4 rect1, glm::vec4 rect2);
};

#endif