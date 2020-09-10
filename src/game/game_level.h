#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
using namespace std;

#include "game_object.h"
#include "../render/sprite_renderer.h"
#include "../core/resource_manager.h"

class GameLevel
{
private:
    void init(vector<vector<unsigned int>> tile_data, unsigned int level_width, unsigned int level_height);
public:
    // 关卡中所有的砖块
    vector<GameObject> bricks_;

    GameLevel(/* args */) {}

    // 从文件中加载关卡
    void Load(const char* file, unsigned level_width, unsigned int level_height);

    // 渲染关卡
    void Draw(SpriteRenderer& renderer);

    // 关卡是否通过（所有兼顾的瓷砖均被摧毁）
    bool IsCompleted();

    // 重置关卡数据
    void Reset();
};


#endif
