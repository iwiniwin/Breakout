#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D scene;
uniform vec2 offset[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main(){
    FragColor = vec4(0.0f);
    vec3 sample[9];
    if(chaos || shake)
        // 为使用卷积核采样周边像素
        for(int i = 0; i < 9; i ++)
            sample[i] = vec3(texture(scene, TexCoords + offset[i]));

    if(chaos){
        // 应用边缘检测核
        for(int i = 0; i < 9; i++)
            FragColor += vec4(sample[i] * edge_kernel[i], 0.0f);
        FragColor.a = 1.0f;
    }else if(confuse){
        // 反相
        FragColor = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }else if(shake){
        // 应用模糊核
        for(int i = 0; i < 9; i ++)
            FragColor += vec4(sample[i] * blur_kernel[i], 0.0f);
        FragColor.a = 1.0f;
    }else{
        FragColor = texture(scene, TexCoords);
    }
}