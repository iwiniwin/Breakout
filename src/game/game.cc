#include <iostream>

#include "game.h"
#include "../core/resource_manager.h"
#include "../render/sprite_renderer.h"
#include "../render/particle.h"
#include "../game/ball_object.h"
#include "../utils/collision.h"
#include "../utils/rect.h"
#include "../utils/circle.h"
#include "GLFW/glfw3.h"

SpriteRenderer* sprite_renderer;
ParticleGenerator* particle_generator;

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

    Shader sprite_shader = ResourceManager::LoadShader("resources/shaders/sprite.vs", "resources/shaders/sprite.frag", nullptr, "sprite");
    sprite_shader.Use().SetInteger("image", 0);
    sprite_shader.SetMatrix4("projection", projection);

    Shader particle_shader = ResourceManager::LoadShader("resources/shaders/particle.vs", "resources/shaders/particle.frag", nullptr, "particle");
    particle_shader.Use().SetInteger("sprite", 0);
    particle_shader.SetMatrix4("projection", projection);

    // 加载纹理
    ResourceManager::LoadTexture("resources/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "ball");
    ResourceManager::LoadTexture("resources/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("resources/textures/block.png", false, "block");
    ResourceManager::LoadTexture("resources/textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("resources/textures/particle.png", true, "particle");

    sprite_renderer = new SpriteRenderer(sprite_shader);
    particle_generator = new ParticleGenerator(particle_shader, ResourceManager::GetTexture("particle"), 500);

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
    // 移动小球
    ball->Move(dt, width_);

    particle_generator->Update(dt, *ball, 2, glm::vec2(ball->radius_ / 2));

    // 碰撞检测
    DoCollisions();

    if(ball->position_.y >= height_){  // 小球接触底部边界，游戏失败
        Reset();
    }
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

        // 绘制粒子
        particle_generator->Draw();  // 保证粒子绘制在其他物体之前，小球之后

        // 绘制小球
        ball->Draw(*sprite_renderer);
    }
}

void Game::DoCollisions(){
    Circle ball_circle(ball->position_, ball->radius_);
    for(GameObject& box : levels_[level_].bricks_){
        if(!box.destroyed_){
            Rect box_rect(box.position_, box.size_);
            CollisionResult result = Collision::Detect(ball_circle, box_rect);
            if(get<0>(result)){
                // 非坚固砖块，销毁
                if(!box.is_solid_)
                    box.destroyed_ = true;

                // 碰撞处理
                Direction dir = get<1>(result);
                glm::vec2 difference = get<2>(result);
                if(dir == kLeft || dir == kRight){  // 水平方向碰撞
                    ball->velocity_.x = -ball->velocity_.x;  // 反转水平速度

                    // 将小球移出砖块内
                    float penetration = ball->radius_ - abs(difference.x);
                    if(dir == kLeft)  // 在矩形右边碰撞，将球右移
                        ball->position_.x += penetration;  
                    else
                        ball->position_.x -= penetration;
                }else{
                    ball->velocity_.y = -ball->velocity_.y;  // 反转垂直速度

                    float penetration = ball->radius_ - abs(difference.y);
                    if(dir == kUp)
                        ball->position_.y -= penetration;
                    else
                        ball->position_.y += penetration;
                }
            }
        }
    }

    Rect paddle_rect(paddle->position_, paddle->size_);
    CollisionResult result = Collision::Detect(ball_circle, paddle_rect);
    if(!ball->stuck_ && get<0>(result)){
        // 检查碰撞到了挡板的哪个位置，并根据位置来改变速度
        // 小球圆心距离挡板中心越远，水平速度越大
        float paddle_center = paddle->position_.x + paddle->size_.x / 2;
        float distance = (ball->position_.x + ball->radius_) - paddle_center;
        float percentage = distance / (paddle->size_.x / 2);

        float strength = 2.0f;
        glm::vec2 old_velocity = ball->velocity_;
        ball->velocity_.x = kBallVelocity.x * percentage * strength;
        // ball->velocity_.y = - ball->velocity_.y;
        ball->velocity_.y = 1 - abs(ball->velocity_.y);
        // 保证小球总的速度与力量是一致的
        ball->velocity_ = glm::normalize(ball->velocity_) * glm::length(old_velocity);
    }
}

void Game::Reset(){
    // 重置关卡
    for(unsigned int i = 0; i <= level_; i ++)
        levels_[i].Reset();

    // 重置挡板
    paddle->size_ = kPaddleSize;
    paddle->position_ = glm::vec2(width_ / 2 - kPaddleSize.x / 2, height_ - kPaddleSize.y);

    // 重置小球
    ball->Reset(paddle->position_ + glm::vec2(kPaddleSize.x / 2 - kBallRadius, -kBallRadius * 2), kBallVelocity);
}

