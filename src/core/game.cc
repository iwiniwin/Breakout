#include <iostream>

#include "game.h"
#include "resource_manager.h"
#include "../render/sprite_renderer.h"


SpriteRenderer* sprite_renderer;

Game::Game(unsigned int width, unsigned int height){
    width_ = width;
    height_ = height;
}

Game::~Game(){
    delete(sprite_renderer);
}

void Game::Init(){
    
    // 前四个参数依次指定了左，右，下，上边界，后两个参数定义了近平面和远平面的距离
    // 即左上角坐标为(0, 0)，右下角坐标为(width_, height_)
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_), static_cast<float>(height_), 0.0f, -1.0f, 1.0f);

    Shader shader = ResourceManager::LoadShader("resources/shaders/sprite.vs", "resources/shaders/sprite.frag", nullptr, "sprite");
    shader.Use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);

    sprite_renderer = new SpriteRenderer(shader);

    // 加载纹理
    ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("resources/textures/block_solid.png", GL_TRUE, "block_solid");
    ResourceManager::LoadTexture("resources/textures/block.png", GL_TRUE, "block");

    // 加载关卡
    GameLevel one;
    one.Load("resources/levels/one.lvl", width_, height_ * 0.5);
    levels_.push_back(one);

    GameLevel two;
    two.Load("resources/levels/two.lvl", width_, height_ * 0.5);
    levels_.push_back(two);

    GameLevel three;
    three.Load("resources/levels/three.lvl", width_, height_ * 0.5);
    levels_.push_back(three);

    GameLevel four;
    four.Load("resources/levels/four.lvl", width_, height_ * 0.5);
    levels_.push_back(four);

    // 设置当前关卡
    level_ = 0;
}

void Game::Update(float dt){

}

void Game::ProcessInput(float dt){

}

void Game::Render(){
    if(state_ == KGameActive){
        // 绘制背景
        Texture2D texture = ResourceManager::GetTexture("background");
        sprite_renderer->DrawSprite(texture, glm::vec2(0, 0), glm::vec2(width_, height_), 0.0f);

        // 绘制关卡
        levels_[level_].Draw(*sprite_renderer);
    }
}

