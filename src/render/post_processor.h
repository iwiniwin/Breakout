#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "shader.h"
#include "texture.h"

class PostProcessor
{
private:
    unsigned int ms_fbo_;  // 多重采样帧缓冲
    unsigned int fbo_;  // 普通帧缓冲
    unsigned int rbo_;  // 用于多重采样帧缓冲的渲染缓冲对象
    unsigned int vao_;

    void initRenderData();
public:
    Shader shader_;
    Texture2D texture_;  // 帧缓冲的颜色附件
    unsigned int width_, height_;

    // confuse，颠倒效果，反相
    // chaos, 混沌效果，边缘检测+旋转偏移
    // shake, 晃动效果，模糊+偏移
    bool confuse_, chaos_, shake_;

    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    // 用于在场景渲染之前调用
    void BeginRender();
    // 用于在场景渲染之后调用
    void EndRender();
    void Render(float time);
};

#endif