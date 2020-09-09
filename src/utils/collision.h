#ifndef COLLISION_H
#define COLLISION_H

#include <tuple>

#include "glm.hpp"
#include "rect.h"
#include "circle.h"

enum Direction {
    kUp,
    kRight,
    kDown,
    kLeft
};

typedef std::tuple<bool, Direction, glm::vec2> CollisionResult;

class Collision
{
private:
    Collision() {};
public:
    static bool Detect(Rect rect1, Rect rect2);
    static CollisionResult Detect(Circle circle, Rect rect);

    static Direction CaculateDirection(glm::vec2 target);
};

#endif