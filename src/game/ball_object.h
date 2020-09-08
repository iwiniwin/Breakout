#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "../render/texture.h"
#include "glm.hpp"
#include "../core/game.h"


class BallObject : public GameObject
{

public:
    float radius_;
    // 是否卡住，是否可以移动
    bool stuck_;

    BallObject(/* args */);
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

    // 根据球的速度移动球
    glm::vec2 Move(float dt, unsigned int window_width);

    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif