#include <iostream>

#include "game.h"
#include "resource_manager.h"
#include "../render/sprite_renderer.h"
#include "../game/ball_object.h"
#include "GLFW/glfw3.h"

SpriteRenderer* sprite_renderer;

// 挡板大小
const glm::vec2 kPaddleSize(100, 20);
// 挡板速度
const float kPaddleVelocity(500.0f);
GameObject* paddle;

// 球的速度
const glm::vec2 kBallVelocity(100.0f, -350.0f);
// 球的半径
const float kBallRadius = 12.5f;
BallObject *ball;

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
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "ball");
    ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
    ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");

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

    // 初始化挡板
    glm::vec2 paddle_pos = glm::vec2(width_ / 2 - kPaddleSize.x / 2, height_ - kPaddleSize.y);
    paddle = new GameObject(paddle_pos, kPaddleSize, ResourceManager::GetTexture("paddle"));

    // 初始化小球
    glm::vec2 ball_pos = paddle_pos + glm::vec2(kPaddleSize.x / 2 - kBallRadius, -kBallRadius * 2);
    ball = new BallObject(ball_pos, kBallRadius, kBallVelocity, ResourceManager::GetTexture("ball"));
}

void Game::Update(float dt){
    ball->Move(dt, width_);
}

void Game::ProcessInput(float dt){
    if(state_ == KGameActive){
        float velocity = kPaddleVelocity * dt;
        // 移动挡板
        if(keys_[GLFW_KEY_A]){
            paddle->position_.x -= velocity;
            if(paddle->position_.x < 0)
                paddle->position_.x = 0;
            if(ball->stuck_){
                ball->position_ = paddle->position_ + glm::vec2(kPaddleSize.x / 2 - kBallRadius, -kBallRadius * 2);
            }
        }
            
        if(keys_[GLFW_KEY_D]){
            paddle->position_.x += velocity;
            if(paddle->position_.x > width_ - paddle->size_.x)
                paddle->position_.x = width_ - paddle->size_.x;
            if(ball->stuck_){
                ball->position_ = paddle->position_ + glm::vec2(kPaddleSize.x / 2 - kBallRadius, -kBallRadius * 2);
            }
        }
            
        if(keys_[GLFW_KEY_SPACE])
            ball->stuck_ = false;
    }
}

void Game::Render(){
    if(state_ == KGameActive){
        // 绘制背景
        Texture2D texture = ResourceManager::GetTexture("background");
        sprite_renderer->DrawSprite(texture, glm::vec2(0, 0), glm::vec2(width_, height_), 0.0f);

        // 绘制关卡
        levels_[level_].Draw(*sprite_renderer);

        // 绘制挡板
        paddle->Draw(*sprite_renderer);

        // 绘制小球
        ball->Draw(*sprite_renderer);
    }
}

