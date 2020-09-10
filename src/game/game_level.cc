#include "game_level.h"

#include <fstream>
#include <sstream>
#include <iostream>

void GameLevel::Load(const char* file, unsigned level_width, unsigned int level_height){
    // 清空旧的数据
    bricks_.clear();

    unsigned int tile_code;
    GameLevel level;

    string line;
    ifstream fstream(file);
    vector<vector<unsigned int>> tile_data;
    if(fstream){
        // 读每行
        while(getline(fstream, line)){
            istringstream sstream(line);
            vector<unsigned int> row;
            // 读每个数字
            while(sstream >> tile_code)
                row.push_back(tile_code);
            tile_data.push_back(row);
        }
        if(tile_data.size() > 0)
            init(tile_data, level_width, level_height);
    }
}

// 渲染所有未被破坏的砖块
void GameLevel::Draw(SpriteRenderer& renderer){
    for(GameObject& tile : bricks_)
        if(!tile.destroyed_)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted(){
    for(GameObject& tile : bricks_)
        if(!tile.is_solid_ && !tile.destroyed_)  // 如果还有非坚固的砖块没有被摧毁，就不通过
            return false;
    return true;
}

void GameLevel::init(vector<vector<unsigned int>> tile_data, unsigned int level_width, unsigned int level_height){
    unsigned int height = tile_data.size();
    if(height <= 0) return;
    unsigned int width = tile_data[0].size();
    float unit_width = level_width / static_cast<float>(width), unit_height = level_height / height;

    for(unsigned int y = 0; y < height; y ++){
        for(unsigned int x = 0; x < width; x ++){
            if(tile_data[y][x] == 1){  // 坚固砖块
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.is_solid_ = true;
                bricks_.push_back(obj);
            }else if(tile_data[y][x] > 1){
                glm::vec3 color = glm::vec3(1.0f);
                if(tile_data[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if(tile_data[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if(tile_data[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if(tile_data[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                bricks_.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}

void GameLevel::Reset(){
    for(GameObject& tile : bricks_)
        tile.destroyed_ = false;
}