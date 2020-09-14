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
    // 创建一个多重采样渲染缓冲对象，这里的8表示样本的数量
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width_, height_);
    // 将渲染缓冲对象附加到帧缓冲上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo_);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    texture_.Generate(width_, height_, NULL);
    /*
        将纹理附件附加到帧缓冲上
        参数1，目标帧缓冲类型
        参数2，附件的附件的类型
        参数3，附件的纹理的类型
        参数4，附加的实际的纹理
        参数5，Mipmap level
    */
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
    glUniform1iv(glGetUniformLocation(shader_.id_, "edge_kernel"), 9, edge_kernel);
    float blur_kernel[9] = {
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16,
    };  
    glUniform1fv(glGetUniformLocation(shader_.id_, "blur_kernel"), 9, blur_kernel);
}

// 在场景渲染前调用，使场景全部被渲染到多重采样帧缓冲上
void PostProcessor::BeginRender(){
    glBindFramebuffer(GL_FRAMEBUFFER, ms_fbo_);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

// 在场景渲染完成后调用，将多重采样帧缓冲的内容，块传送到普通的帧缓冲，这样做是为了便于对多重采样帧缓冲的rbo内容进行采样
void PostProcessor::EndRender(){
    glBindFramebuffer(GL_READ_BUFFER, ms_fbo_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
    glBlitFramebuffer(0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// 此函数完成对场景进行后处理任务
// 基本流程是，对已经从多重采样帧缓冲的rbo中获得数据的纹理附件进行采样，然后根据不同的参数进行后处理
// 最后将处理后的结果渲染为一个充满屏幕的四边形
void PostProcessor::Render(float time){
    shader_.Use();
    shader_.SetFloat("time", time);
    shader_.SetInteger("confuse", confuse_);
    shader_.SetInteger("chaos", chaos_);
    shader_.SetInteger("shake", shake_);

    glActiveTexture(GL_TEXTURE0);
    texture_.Bind();
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// 初始化渲染数据，构建辅屏四边形VAO
void PostProcessor::initRenderData(){
    unsigned int vbo;
    float vertices[] = {
        // Pos        // Tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(vao_);
}