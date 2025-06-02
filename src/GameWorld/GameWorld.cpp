#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Background.hpp"
#include "pvz/GameObject/Sunflower.hpp"  // 包含向日葵头文件
#include "pvz/GameObject/Grid.hpp"        // 包含种植位头文件
#include "pvz/utils.hpp"                  // 包含常量定义

void GameWorld::Init() {
    // 创建背景
    auto background = std::make_shared<Background>(
        ImageID::BACKGROUND,
        WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
        LayerID::BACKGROUND,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        AnimID::NO_ANIMATION
    );
    AddObject(background);

    // 创建种植网格 (5行9列)
    for (int row = 0; row < GAME_ROWS; ++row) {
        for (int col = 0; col < GAME_COLS; ++col) {
            // 计算每个格子的中心坐标
            int x = FIRST_COL_CENTER + col * LAWN_GRID_WIDTH;
            int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

            // 创建Grid对象，并绑定回调函数
            auto grid = std::make_shared<Grid>(x, y, [this](int gridX, int gridY) {
                // 当Grid被点击时，调用AddPlant方法
                AddPlant(gridX, gridY);
            });

            // 将Grid添加到游戏对象列表
            AddObject(grid);
        }
    }
}

LevelStatus GameWorld::Update() {
    // 更新所有游戏对象
    for (auto& obj : m_gameObjects) {
        obj->Update();
    }

    // 这里暂时返回ONGOING，表示游戏进行中
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
    // 清理游戏对象
    m_gameObjects.clear();
}

void GameWorld::AddPlant(int x, int y) {
    // 在指定位置创建向日葵
    auto sunflower = std::make_shared<Sunflower>(x, y);
    AddObject(sunflower);
}
