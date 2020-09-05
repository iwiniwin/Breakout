#include <iostream>

#include "texture.h"

Texture2D::Texture2D()
    : width_(0), height_(0), internal_format_(GL_RGB), image_format_(GL_RGB), wrap_s_(GL_REPEAT), wrap_t_(GL_REPEAT), filter_min_(GL_LINEAR), filter_max_(GL_LINEAR)
{
    glGenTextures(1, &id_);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data){
    width_ = width;
    height_ = height;

    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width_, height_, 0, image_format_, GL_UNSIGNED_BYTE, data);
    
    // 设置纹理环绕，过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const{
    glBindTexture(GL_TEXTURE_2D, id_);
}