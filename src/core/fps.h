#ifndef FPS_H
#define FPS_H

class FPS
{
private:
    FPS(/* args */) {};
    static float time_;
    static float count_ ;

    static float rate_;
public:
    static float Caculate(float dt);
    static void Reset();
};

#endif

