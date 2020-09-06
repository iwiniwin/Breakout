#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader){
    shader_ = shader;
    intRenderData();
}

SpriteRenderer::~SpriteRenderer(){
    glDeleteVertexArrays(1, &quad_vao_);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color){
    shader_.Use();
    glm::mat4 model(1.0f);

    // 正常情况下应该是先缩放，再旋转，再位移，但是矩阵乘法是从右到左的，所以这里顺序正好反过来

    // 5. 移动到指定位置
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // 4. 还原之前为旋转做的位移
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));

    // 3. 2D游戏，围绕z轴旋转
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));

    // 2. 将中心点（即锚点）移动到纹理中心，以便旋转是围绕中心进行的
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    // 1. 先缩放
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader_.SetMatrix4("model", model);
    shader_.SetVector3f("spriteColor", color);

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // 绘制方形
    glBindVertexArray(quad_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::intRenderData(){
    unsigned int vbo;
    // (0, 1)对应的纹理坐标是(0, 0)是因为，(0, 1)经正交投影矩阵变换后就是左上角是(0, 0)，
    float vertices[] = {
        // Pos     // TexCoords
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &quad_vao_);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quad_vao_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}