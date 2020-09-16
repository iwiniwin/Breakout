#ifndef PARTICLE_H 
#define PARTICLE_H

#include <vector>

#include "shader.h"
#include "texture.h"
#include "../game/game_object.h"
#include "glm.hpp"
using namespace std;


struct Particle {
    glm::vec2 position_, velocity_;
    glm::vec4 color_;
    float life_;  // 生命值

    Particle()
        : position_(0.0f), velocity_(0.0f), color_(1.0f), life_(0.0f) {}
};

// 粒子生成器
class ParticleGenerator
{
private:
    // 存放所有产生的粒子
    vector<Particle> particles_;
    // 产生的粒子数量
    unsigned int amount_;

    Shader shader_;
    Texture2D texture_;

    unsigned int vao_;

    float* instance_data_;  // 实例化用的数据
    unsigned int instance_vbo_;  // 实例化用的VBO
    
    void init();
    unsigned int firstUnusedParticle();
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

public:
    ParticleGenerator(Shader shader, Texture2D texture, unsigned amount);
    ~ParticleGenerator();

    // 更新所有粒子
    void Update(float dt, GameObject& object, unsigned new_particles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

    // 渲染所有粒子
    void Draw();
};

#endif