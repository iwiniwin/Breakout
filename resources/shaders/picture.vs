#version 330 core
layout (location = 0) in vec4 vertex;  // <vec2 position, vec2 texcoords>

out vec2 TexCoords;

uniform bool flip_vertically;

void main(){
    gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
    TexCoords = vertex.zw;
    if(flip_vertically)
        TexCoords.y = 1.0 - TexCoords.y;
}