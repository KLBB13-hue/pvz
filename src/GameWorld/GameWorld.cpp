#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Background.hpp"
#include "pvz/GameObject/Sunflower.hpp"  // 包含向日葵头文件
#include "pvz/GameObject/Grid.hpp"        // 包含种植位头文件
#include "pvz/utils.hpp"                  // 包含常量定义
#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameObject/ShovelButton.hpp"


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

            auto grid = std::make_shared<Grid>(x, y, this);
            AddObject(grid);
        }
    }
    // 初始化状态
    m_selectedSeed = nullptr;
    m_shovelSelected = false;
    // 创建种子按钮
    const int seedButtonY = WINDOW_HEIGHT - 44;
    int seedButtonX = 130;

    // 向日葵种子
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_SUNFLOWER,
        seedButtonX, seedButtonY,
        50,  // 价格
        this
    ));

    // 豌豆射手种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_PEASHOOTER,
        seedButtonX, seedButtonY,
        100, this
    ));

    // 坚果墙种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_WALLNUT,
        seedButtonX, seedButtonY,
        50, this
    ));

    // 樱桃炸弹种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_CHERRY_BOMB,
        seedButtonX, seedButtonY,
        150, this
    ));

    // 双发射手种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_REPEATER,
        seedButtonX, seedButtonY,
        200, this
    ));

    // 创建铲子按钮
    AddObject(std::make_shared<ShovelButton>(
        600, WINDOW_HEIGHT - 40, this
    ));
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

