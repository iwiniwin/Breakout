#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
private:
    Shader shader_;
    unsigned int quad_vao_;
    // 初始化VAO，顶点数据
    void intRenderData();
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();
    // 绘制一个贴图
    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

#endif