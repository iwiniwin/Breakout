#include <iostream>

#include "gtc/matrix_transform.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "text_renderer.h"
#include "../core/resource_manager.h"

TextRenderer::TextRenderer(Shader& shader)
    : shader_(shader)
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // 每个四边形需要6个顶点，每个顶点4个float变量
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::Load(std::string font, unsigned font_size){
    characters_.clear();
    // 初始化FreeType库
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if(FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font :\n" << font << std::endl;

    // 定义字体大小，0，font_size表示字体的宽高，宽度值为0表示通过给定的高度动态计算宽度
    FT_Set_Pixel_Sizes(face, 0, font_size);
    // 禁用字节对齐限制
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // 生成ASCII字符集的前128个字符
    for(unsigned char c = 0; c < 128; c++){
        // 加载一个字形，FT_LOAD_RENDER表示创建一个8位的灰度图
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph :\n" << c << std::endl;
            continue;
        }
        // 生成纹理
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),  // 字形大小
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),  // 从基准线到字形左部/顶部的偏移量
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters_.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // 清理FreeType资源
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color){
    shader_.Use();
    shader_.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao_);

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c ++){
        Character ch = characters_[*c];
        float xpos = x + ch.bearing_.x * scale;
        // 根据基准线调整字符的向下偏移，这里受投影矩阵的影响(0, 0)是左上角
        float ypos = y + (characters_['H'].bearing_.y - ch.bearing_.y) * scale;

        float w = ch.size_.x * scale;
        float h = ch.size_.y * scale;

        // 对每个字符更新VBO
        // float vertices[6][4] = {
        //     { xpos,     ypos + h,   0.0, 1.0 },
        //     { xpos + w, ypos,       1.0, 0.0 },
        //     { xpos,     ypos,       0.0, 0.0 },

        //     { xpos,     ypos + h,   0.0, 1.0 },
        //     { xpos + w, ypos + h,   1.0, 1.0 },
        //     { xpos + w, ypos,       1.0, 0.0 }
        // };

        // 优化，使用GL_TRIANGLE_STRIP渲染方式，节省需要传递的数据量
        float vertices[6][4] = {
            { xpos,     ypos,       0.0, 0.0 },
            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 },
            { xpos + w, ypos + h,   1.0, 1.0 },
        };

        // 在四边形上绘制纹理
        glBindTexture(GL_TEXTURE_2D, ch.texture_id_);
        // 更新VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        /*
            glBufferSubData用于填充缓冲的特定区域
            参数1，目标缓冲的类型
            参数2，偏移量
            参数3，数据大小
            参数4，数据本身
        */
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // 绘制四边形
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        // 更新位置到下一个字形的原点，单位是1/64像素
        x += (ch.advance_ >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}