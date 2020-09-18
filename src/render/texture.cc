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
    /*
        生成一个纹理
        参数1，指定了纹理目标
        参数2，为纹理指定多级渐远纹理的级别
        参数3，指定纹理的储存格式
        参数4，设置最终纹理的宽
        参数5，设置最终纹理的高
        参数6，应该总被设置为0，历史遗留问题
        参数7，定义了源图的格式
        参数8，定义了源图的数据类型
        参数9，真正的图像数据
    */ 
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