#include "ball_object.h"

BallObject::BallObject()
    : GameObject(), radius_(12.5f), stuck_(true), sticky_(false), pass_through_(false) {}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, glm::vec3 color)
    : GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, color, velocity), radius_(radius), stuck_(true), sticky_(false), pass_through_(false) {}

glm::vec2 BallObject::Move(float dt, unsigned int window_width){
    if(!stuck_){
        position_ += velocity_ * dt;
        
        // 检查小球是否超出边界

        if(position_.x <= 0.0f){
            velocity_.x = -velocity_.x;
            position_.x = 0.0f;
        }else if(position_.x + size_.x > window_width){
            velocity_.x = -velocity_.x;
            position_.x = window_width - size_.x;
        }
        if(position_.y <= 0.0f){
            velocity_.y = - velocity_.y;
            position_.y = 0.0f;
        }
    }
    return position_;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity, glm::vec3 color){
    position_ = position;
    velocity_ = velocity;
    stuck_ = true;
    sticky_ = false;
    pass_through_ = false;
    color_ = color;
}