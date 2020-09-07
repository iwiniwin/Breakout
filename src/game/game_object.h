#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glm.hpp"
#include "../render/texture.h"
#include "../render/sprite_renderer.h"

class GameObject
{
public:
    glm::vec2 position_, size_, velocity_;
    glm::vec3 color_;
    float rotation_;
    // 是否坚固不可摧毁
    bool is_solid_;
    // 是否被摧毁
    bool destroyed_;

    Texture2D sprite_;

    GameObject(/* args */);
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void Draw(SpriteRenderer& render);
};

#endif