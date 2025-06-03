#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Background.hpp"
#include "pvz/GameObject/Sunflower.hpp"  // 包含向日葵头文件
#include "pvz/GameObject/Grid.hpp"        // 包含种植位头文件
#include "pvz/utils.hpp"                  // 包含常量定义
#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameObject/ShovelButton.hpp"
#include "pvz/GameObject/Sun.hpp"


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

    // 创建阳光计数文本显示（位置在左上角）
    m_sunText = std::make_shared<TextBase>(
        50, WINDOW_HEIGHT - 78,                          // 坐标位置 (x, y)
        "50",                             // 初始文本
        0.0, 0.0, 0.0,                    // 黄色 (R,G,B)
        false                             // 不居中
    );
    // 初始化状态
    m_selectedSeed = nullptr;
    m_shovelSelected = false;
    // 创建种子按钮
    const int seedButtonY = WINDOW_HEIGHT - 44;
    int seedButtonX = 130;
    m_sunDropTimer = 180;

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

void GameWorld::AddSun(int amount) {
    m_sunCount += amount;  // 增加阳光数量

    // 更新阳光文本显示
    char buffer[20];
    sprintf(buffer, "%d", m_sunCount);
    m_sunText->SetText(buffer);
}

LevelStatus GameWorld::Update() {
    // 更新阳光文本显示（确保实时更新）
    char buffer[20];
    sprintf(buffer, "%d", m_sunCount);
    m_sunText->SetText(buffer);
    // 更新所有游戏对象
    auto it = m_gameObjects.begin();
    while (it != m_gameObjects.end()) {
        auto& obj = *it;
        if (obj->IsDead()) { // 检查死亡状态
            it = m_gameObjects.erase(it);
        } else {
            obj->Update();
            ++it;
        }
    }

    // 阳光掉落逻辑
    if (--m_sunDropTimer <= 0) {
        // 生成随机x坐标 [75, WINDOW_WIDTH-75]
        int sunX = randInt(75, WINDOW_WIDTH - 75);
        int sunY = WINDOW_HEIGHT - 1; // 从屏幕顶部生成

        // 创建掉落阳光
        auto sun = std::make_shared<Sun>(
            sunX, sunY,
            Sun::FALLING_SUN,
            this
        );
        AddObject(sun);

        m_sunDropTimer = 300; // 重置计时器（10秒/300tick）
    }


    // 这里暂时返回ONGOING，表示游戏进行中
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
    // 清理游戏对象
    m_gameObjects.clear();
}

void GameWorld::AddPlant(int x, int y) {
    if (m_sunCount >= 50)
    {
        auto sunflower = std::make_shared<Sunflower>(x, y, this);
        AddObject(sunflower);

        // 扣除阳光
        m_sunCount -= 50;
        // 扣除阳光后更新显示
        char buffer[20];
        sprintf(buffer, "%d", m_sunCount);
        m_sunText->SetText(buffer);
    }
}



