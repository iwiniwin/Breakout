#include "collision_detect.h"

bool CollisionDetect::Detect(Rect rect1, Rect rect2){
    if(rect1.right_ > rect2.left_ && rect2.right_ > rect1.left_ && rect1.bottom_ > rect2.top_ && rect2.bottom_ > rect1.top_)
        return true;
    return false; 
}

bool CollisionDetect::Detect(Circle circle, Rect rect){
    // 计算矩形的中心
    glm::vec2 rect_half_extents(rect.size_.x / 2, rect.size_.y / 2);
    glm::vec2 rect_center(rect.left_ + rect_half_extents.x, rect.top_ + rect_half_extents.y);
    // 计算圆心与矩形中心的差量
    glm::vec2 difference = circle.center_ - rect_center;
    glm::vec2 clamped = glm::clamp(difference, - rect_half_extents, rect_half_extents);
    // 计算矩形距离圆最近的点
    glm::vec2 closest = rect_center + clamped;

    difference = closest - circle.center_;
    return glm::length(difference) < circle.radius_;
}