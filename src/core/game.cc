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
    

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_), static_cast<float>(height_), 0.0f, -1.0f, 1.0f);

    Shader shader = ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    shader.Use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);

    ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
    sprite_renderer = new SpriteRenderer(shader);
}

void Game::Update(float dt){

}

void Game::ProcessInput(float dt){

}

void Game::Render(){
    Texture2D texture = ResourceManager::GetTexture("face");
    sprite_renderer->DrawSprite(texture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

