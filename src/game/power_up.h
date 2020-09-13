#ifndef POWER_UP_H
#define POWER_UP_H

#include "glm.hpp"
#include "../game/game_object.h"

// 道具块大小
const glm::vec2 kSize(60, 20);

// 道具块下落速度
const glm::vec2 kVelocity(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
    // 道具类型
    std::string type_;
    // 有效时长
    float duration_;
    // 是否被激活
    bool activated_;

    PowerUp(std::string type, glm::vec3 color, float duration, glm::vec2 position, Texture2D texture)
        : GameObject(position, kSize, texture, color, kVelocity), type_(type), duration_(duration), activated_() {}
};

#endif