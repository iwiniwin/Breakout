#include "fps.h"

float FPS::time_ = 0.0f;
float FPS::count_ = 0.0f;
float FPS::rate_ = 0.0f;

// 根据dt（单位秒）计算fps
float FPS::Caculate(float dt){
    time_ += dt;
    count_ ++;
    if(time_ >= 1.0f){
        time_ -= 1;
        rate_ = count_;
        count_ = 0;
    }
    return rate_;
}


void FPS::Reset(){
    time_ = 0.0f;
    count_ = 0.0f;
    rate_ = 0.0f;
}