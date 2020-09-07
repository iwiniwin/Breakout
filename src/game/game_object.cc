#include "game_object.h"

GameObject::GameObject()
    : position_(0, 0), size_(1, 1), velocity_(0.0f), color_(1.0f), rotation_(0.0f), sprite_(), is_solid_(false), destroyed_(false) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : position_(pos), size_(size), velocity_(velocity), color_(color), rotation_(0.0f), sprite_(sprite), is_solid_(false), destroyed_(false) {}


void GameObject::Draw(SpriteRenderer& render){
    render.DrawSprite(sprite_, position_, size_, rotation_, color_);
}