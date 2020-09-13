#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texcoords>

out vec2 TexCoords;

uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;

void main(){
    gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
    TexCoords = vertex.zw;

    if(chaos){  // 圆形旋转
        float strength = 0.3;
        TexCoords = vec2(TexCoords.x + sin(time) * strength, TexCoords.y + cos(time) * strength);
    }else if(confuse){  // 反转坐标
        TexCoords = vec2(1.0 - TexCoords.x, 1.0 - TexCoords.y);
    }

    if(shake){  // 晃动效果，微量移动顶点位置
        float strength = 0.01;
        gl_Position.x += cos(time * 10) * strength;
        gl_Position.y += cos(time * 15) * strength;
    }
}