#include "collision.h"

// 矩形与矩形碰撞检测
bool Collision::Detect(Rect rect1, Rect rect2){
    if(rect1.right_ > rect2.left_ && rect2.right_ > rect1.left_ && rect1.bottom_ > rect2.top_ && rect2.bottom_ > rect1.top_)
        return true;
    return false; 
}

// 圆形与矩形碰撞检测
CollisionResult Collision::Detect(Circle circle, Rect rect){
    // 计算矩形的中心
    glm::vec2 rect_half_extents(rect.size_.x / 2, rect.size_.y / 2);
    glm::vec2 rect_center(rect.left_ + rect_half_extents.x, rect.top_ + rect_half_extents.y);
    // 计算圆心与矩形中心的差量
    glm::vec2 difference = circle.center_ - rect_center;
    glm::vec2 clamped = glm::clamp(difference, - rect_half_extents, rect_half_extents);
    // 计算矩形距离圆最近的点
    glm::vec2 closest = rect_center + clamped;

    difference = closest - circle.center_;

    if(glm::length(difference) < circle.radius_)
        return std::make_tuple(true, CaculateDirection(difference), difference);
    else
        return std::make_tuple(false, kUp, glm::vec2(0, 0));
}

// 判断目标矢量，更接近上下左右方向的哪一个
Direction Collision::CaculateDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // 上
        glm::vec2(1.0f, 0.0f),  // 右
        glm::vec2(0.0f, -1.0f),  // 下
        glm::vec2(-1.0f, 0.0f)  // 左
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for(unsigned int i = 0; i < 4; i ++){
        // 点积越大，则角度越小，越接近
        float product = glm::dot(glm::normalize(target), compass[i]);
        if(product > max){
            max = product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}