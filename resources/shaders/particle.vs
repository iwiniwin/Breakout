#version 330 core
layout (location = 0) in vec4 vertex;   // <vec2 position, vec2 texcoords>
layout (location = 1) in vec2 offset;  // 将offset作为一个顶点属性
layout (location = 2) in vec4 color;  // 将color作为一个顶点属性

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;

void main(){
    float scale = 10.0f;
    TexCoords = vertex.zw;
    ParticleColor = color;
    // 将粒子进行缩放与偏移
    gl_Position = projection * vec4(vertex.xy * scale + offset, 0.0f, 1.0f);
}
