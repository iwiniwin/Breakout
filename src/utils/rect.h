#ifndef RECT_H
#define RECT_H

#include "glm.hpp"

class Rect
{
public:
    // 左上角横坐标
    float left_;
    // 左上角竖坐标
    float top_;
    // 右上角横坐标
    float right_;
    // 右上角竖坐标
    float bottom_;
    // 矩形大小
    glm::vec2 size_;

    Rect(float left, float top, float right, float bottom);
    Rect(glm::vec2 left_top, glm::vec2 size);
    Rect(float left, float top, glm::vec2 size);
};

#endif