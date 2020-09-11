#include "post_processor.h"

#include <iostream>

#include "GLFW/glfw3.h"

PostProcessor::PostProcessor(Shader shader, unsigned int width, unsigned int height)
    : shader_(shader), texture_(), width_(width), height_(height), confuse_(false), chaos_(false), shake_(false)
{
    glGenFramebuffers(1, &ms_fbo_);
    glGenFramebuffers(1, &fbo_);
    glGenRenderbuffers(1, &rbo_);

    glBindFramebuffer(GL_FRAMEBUFFER, ms_fbo_);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width_, height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo_);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    texture_.Generate(width_, height_, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_.id_, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    initRenderData();
    shader_.Use().SetInteger("scene", 0, true);
    float offset = 1.0f / 300.0f;
    float offsets[9][2] = {
        { -offset,   offset  },  // 左上
        { 0.0f,      offset  },  // 正上
        { offset,    offset  },  // 右上
        { -offset,   0.0f    },  // 左中
        { 0.0f,      0.0f    },  // 中心
        { offset,    0.0f    },  // 右中
        { -offset,   -offset },  // 左下
        { 0.0f,      -offset },  // 正下
        { offset,    -offset },  // 右下
    }; 
    glUniform2fv(glGetUniformLocation(shader_.id_, "offsets"), 9, (float*)offsets);
    int edge_kernel[9] = {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };
    glUniform1iv(glGetUniformLocation(shader.id_, "edge_kernel"), 9, edge_kernel);
}