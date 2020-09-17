#ifndef DISPLAY_H
#define DISPLAY_H

#include "../render/shader.h"

class Display
{
private:
    static unsigned int picture_vao_;
    static Shader picture_shader_;
    Display(/* args */){ };
    static void init();
public:
    static void ShowPicture(unsigned int texture_id, bool flip_vertically = false);
};

#endif