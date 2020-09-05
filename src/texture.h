#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

class Texture2D
{
public:
    // 纹理对象ID
    unsigned int id_;
    // 纹理大小
    unsigned int width_, height_;
    // 纹理格式
    unsigned int internal_format_;
    unsigned int image_format_;

    // 纹理s轴的环绕方式
    unsigned int wrap_s_;
    // 纹理t轴的环绕方式
    unsigned int wrap_t_;

    // 纹理过滤方式
    unsigned int filter_min_;
    unsigned int filter_max_;

    Texture2D(/* args */);
    
    // 根据数据生成纹理
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // 绑定纹理到GL_TEXTURE_2D目标
    void Bind() const;
};

#endif