#include "display.h"
#include "../core/resource_manager.h"

unsigned int Display::picture_vao_ = 0;
Shader Display::picture_shader_;

void Display::init(){
    picture_shader_ = ResourceManager::LoadShader("resources/shaders/picture.vs", "resources/shaders/picture.frag", nullptr, "picture");
    picture_shader_.Use().SetInteger("picture", 0);
    unsigned int vbo;
    glGenVertexArrays(1, &picture_vao_);

    glGenBuffers(1, &vbo);
    // 四分之一屏幕大小画中画
    float vertices[] = {
        // Pos     // TexCoords
        0.25f, 1.0f, 0.0f, 1.0f,
        0.25f, 0.25f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.25f, 1.0f, 0.0f,
    };

    glBindVertexArray(picture_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Display::ShowPicture(unsigned int texture_id, bool flip_vertically){
    if (picture_vao_ == 0)
        init();

    picture_shader_.Use();
    picture_shader_.SetFloat("flip_vertically", flip_vertically);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindVertexArray(picture_vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glUseProgram(0);
}