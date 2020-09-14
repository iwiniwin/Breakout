#include "rect.h"

Rect::Rect(float left, float top, float right, float bottom)
    : left_(left), top_(top), right_(right), bottom_(bottom), size_(glm::vec2(right - left, bottom - top)) {}

Rect::Rect(glm::vec2 left_top, glm::vec2 size) {
    left_ = left_top.x;
    top_ = left_top.y;
    right_ = left_ + size.x;
    bottom_ = top_ + size.y;
    size_ = size;
}

Rect::Rect(float left, float top, glm::vec2 size) {
    left_ = left;
    top_ = top;
    right_ = left + size.x;
    bottom_ = top + size.y;
    size_ = size;
}
    