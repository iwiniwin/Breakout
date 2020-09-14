#ifndef GAME_H
#define GAME_H

#include <vector>
using namespace std;

#include "game_level.h"
#include "power_up.h"

// 当前的游戏状态
enum GameState {
    KGameActive,
    kGameMenu,
    kGameWin
};


class Game
{
public:
    // 游戏状态
    GameState state_;

    bool keys_[1024];
    bool keys_processed_[1024];  // 记录按键事件是否被处理

    // 游戏分辨率
    unsigned int width_, height_;

    // 游戏中所有关卡
    vector<GameLevel> levels_;
    // 当前关卡
    unsigned int level_;

    // 所有道具
    vector<PowerUp> power_ups_;

    // 玩家生命值
    unsigned int life_;

    Game(unsigned int width, unsigned int height);
    ~Game();
    // 初始化游戏状态（加载所有的着色器/纹理/关卡）
    void Init();

    // 游戏循环

    // 处理输入
    void ProcessInput(float dt);
    // 更新游戏设置状态
    void Update(float dt);
    // 渲染
    void Render();

    // 碰撞检测
    void DoCollisions();

    // 重置所有游戏数据
    void Reset();

    // 重置玩家相关的操作数据
    void ResetPlayer();

    // 在给定的一个砖块位置生成道具
    void SpawnPowerUps(GameObject &block);
    // 更新所有被激活的道具
    void UpdatePowerUps(float dt);
};

#endif