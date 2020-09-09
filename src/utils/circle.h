#ifndef CIRCLE_H
#define CIRCLE_H

#include "glm.hpp"

class Circle
{
public:
    // 圆心
    glm::vec2 center_;
    // 半径
    float radius_;

    Circle(glm::vec2 center, float radius);
};

#endif