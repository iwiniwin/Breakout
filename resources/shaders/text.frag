#version 330 core
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main(){
    // 使用单颜色通道位图中的红色分量作为alpha值
    // 非字形区域的alpha值将是0
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    FragColor = vec4(textColor, 1.0) * sampled;
}