#ifndef COLLISION_DETECT_H
#define COLLISION_DETECT_H


#include "glm.hpp"
#include "rect.h"
#include "circle.h"

class CollisionDetect
{
private:
    CollisionDetect() {};
public:
    static bool Detect(Rect rect1, Rect rect2);
    static bool Detect(Circle circle, Rect rect);
};

#endif