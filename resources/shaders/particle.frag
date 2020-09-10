#version 330 core

in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 FragColor;

uniform sampler2D sprite;

void main(){
    FragColor = texture(sprite, TexCoords) * ParticleColor;
}

