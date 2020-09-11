#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "shader.h"
#include "texture.h"

class PostProcessor
{
private:
    unsigned int ms_fbo_;  // 多重采样帧缓冲
    unsigned int fbo_;
    unsigned int rbo_;  // 用于多重采样帧缓冲的渲染缓冲对象
    unsigned int vao_;

    void initRenderData();
public:
    Shader shader_;
    Texture2D texture_;
    unsigned int width_, height_;
    bool confuse_, chaos_, shake_;

    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    // 用于在场景渲染之前调用
    void BeginRender();
    // 用于在场景渲染之后调用
    void EndRender();
    void Render(float time);
};

#endif