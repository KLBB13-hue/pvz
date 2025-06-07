#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Background.hpp"
#include "pvz/GameObject/Sunflower.hpp"
#include "pvz/GameObject/Peashooter.hpp"
#include "pvz/GameObject/Wallnut.hpp"
#include "pvz/GameObject/CherryBomb.hpp"
#include "pvz/GameObject/Repeater.hpp"
#include "pvz/GameObject/Grid.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameObject/Sun.hpp"
#include "pvz/GameObject/ShovelButton.hpp"
#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameObject/SpecificZombies.hpp"

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
    m_grids.clear();
    for (int row = 0; row < GAME_ROWS; ++row) {
        for (int col = 0; col < GAME_COLS; ++col) {
            int x = FIRST_COL_CENTER + col * LAWN_GRID_WIDTH;
            int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

            auto grid = std::make_shared<Grid>(x, y, this);
            AddObject(grid);
            m_grids.push_back(grid);
        }
    }

    // 创建阳光计数文本显示
    m_sunText = std::make_shared<TextBase>(
        50, WINDOW_HEIGHT - 78,
        "50",
        0.0, 0.0, 0.0,
        false
    );

    // 创建波数文本显示 - 添加在Init()函数末尾
    m_waveText = std::make_shared<TextBase>(
        WINDOW_WIDTH - 160, // x位置
        8,                  // y位置
        "Wave: 1",          // 初始文本
        0.0, 0.0, 0.0,      // 黑色文本
        true                // 居中显示
    );

    // 初始化状态
    m_selectedSeed = nullptr;
    const int seedButtonY = WINDOW_HEIGHT - 44;
    int seedButtonX = 130;
    m_sunDropTimer = 180;


    // 向日葵种子
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_SUNFLOWER,
        seedButtonX, seedButtonY,
        50, 240,this
    ));

    // 豌豆射手种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_PEASHOOTER,
        seedButtonX, seedButtonY,
        100, 240,this
    ));

    // 坚果墙种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_WALLNUT,
        seedButtonX, seedButtonY,
        50, 900,this
    ));

    // 樱桃炸弹种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_CHERRY_BOMB,
        seedButtonX, seedButtonY,
        150, 1200,this
    ));

    // 双发射手种子
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_REPEATER,
        seedButtonX, seedButtonY,
        200, 240,this
    ));

    int shovelX = 600;
    int shovelY = WINDOW_HEIGHT - 40;
    auto shovelButton = std::make_shared<ShovelButton>(shovelX, shovelY, this);
    AddObject(shovelButton);
    m_shovelButton = shovelButton;
}

void GameWorld::AddSun(int amount) {
    m_sunCount += amount;
    char buffer[20];
    sprintf(buffer, "%d", m_sunCount);
    m_sunText->SetText(buffer);
}



LevelStatus GameWorld::Update() {

    char buffer[20];
    sprintf(buffer, "%d", m_sunCount);
    m_sunText->SetText(buffer);

    // 更新波数文本显示 - 添加在Update()函数中合适位置
    char waveBuffer[20];
    sprintf(waveBuffer, "Wave: %d", m_waveCount);
    m_waveText->SetText(waveBuffer);

    // 波数生成逻辑
    if (--m_nextWaveTimer <= 0) {
        GenerateWave(); // 生成新一波僵尸

        // 计算下一波间隔
        m_nextWaveTimer = std::max(150, 600 - 20 * m_waveCount);
    }

    // 检测是否有僵尸到达左边界（失败条件）
    for (auto& obj : m_gameObjects) {
        if (auto zombie = std::dynamic_pointer_cast<Zombie>(obj)) {
            if (zombie->GetX() < 0) {

                // 创建僵尸胜利图片（覆盖整个屏幕）
                auto zombiesWonImage = std::make_shared<Background>(
                    ImageID::ZOMBIES_WON,
                    WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
                    LayerID::UI,  // 放在UI层，确保在最上面
                    WINDOW_WIDTH, WINDOW_HEIGHT,
                    AnimID::NO_ANIMATION
                );
                AddObject(zombiesWonImage);
                return LevelStatus::LOSING;
            }
        }
    }


    bool allZombiesDefeated = true;
    auto it = m_gameObjects.begin();
    while (it != m_gameObjects.end()) {
        auto& obj = *it;
        if (obj->IsDead()) {
            // 如果是植物，清理网格引用
            if (auto plant = dynamic_cast<Plant*>(obj.get())) {
                for (auto& grid : m_grids) {
                    // 使用 GetPlant() 获取 shared_ptr
                    if (auto gridPlant = grid->GetPlant()) {
                        if (gridPlant.get() == plant) {
                            grid->SetPlant(nullptr); // 清空网格引用
                        }
                    }
                }
            }
            it = m_gameObjects.erase(it);
        } else {
            obj->Update();
            ++it;
        }
    }

    if (--m_sunDropTimer <= 0) {
        int sunX = randInt(75, WINDOW_WIDTH - 75);
        int sunY = WINDOW_HEIGHT - 1;
        auto sun = std::make_shared<Sun>(sunX, sunY, Sun::FALLING_SUN, this);
        AddObject(sun);
        m_sunDropTimer = 300;
    }

    // 更新铲子选中状态
    if (m_shovelButton) {
        m_shovelSelected = m_shovelButton->IsSelected();
    }

    // 确保铲子和种子状态互斥
    if (m_selectedSeed != nullptr && m_shovelSelected) {
        // 如果同时选中了种子和铲子，自动取消铲子状态
        SetShovelSelected(false);
        if (m_shovelButton) {
            m_shovelButton->SetSelected(false);
        }
    }

    return LevelStatus::ONGOING;
}


void GameWorld::CleanUp() {
    // 正常清理流程
    m_gameObjects.clear();
    m_grids.clear();

    // 重置游戏状态变量
    m_selectedSeed = nullptr;
    m_sunCount = 50;
    m_waveCount = 0;
    m_nextWaveTimer = 1200;
    m_sunDropTimer = 180;
    m_shovelSelected = false;

    m_sunText.reset();
    m_waveText.reset();


    // 注意：不需要在这里调用Init()，因为GameManager会处理重新初始化
}

// GameWorld.cpp
std::shared_ptr<Grid> GameWorld::GetGridAt(int x, int y) {
    for (auto& grid : m_grids) {
        int gridLeft = grid->GetX() - LAWN_GRID_WIDTH / 2;
        int gridRight = grid->GetX() + LAWN_GRID_WIDTH / 2;
        int gridTop = grid->GetY() - LAWN_GRID_HEIGHT / 2;
        int gridBottom = grid->GetY() + LAWN_GRID_HEIGHT / 2;

        // 添加调试输出
        std::cout << "Checking grid at (" << grid->GetX() << ", " << grid->GetY() << ")"
                  << " - Bounds: [" << gridLeft << "-" << gridRight << "], ["
                  << gridTop << "-" << gridBottom << "]" << std::endl;

        if (x >= gridLeft && x <= gridRight &&
            y >= gridTop && y <= gridBottom) {
            // 添加调试输出
            std::cout << "Grid match found!" << std::endl;
            return grid;
            }
    }
    return nullptr;
}

void GameWorld::RemovePlant(int x, int y) {
    if (auto grid = GetGridAt(x, y)) {
        if (auto plant = grid->GetPlant()) {
            // 直接移除植物对象
            plant->SetDead(true);
            grid->SetPlant(nullptr);

            // 强制更新对象列表
            auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
                [&](const auto& obj) { return obj.get() == plant.get(); });
            if (it != m_gameObjects.end()) {
                m_gameObjects.erase(it);
            }
        }
    }
}

std::shared_ptr<Plant> GameWorld::GetPlantAt(int x, int y) {
    for (auto& obj : m_gameObjects) {
        // 只检测植物对象
        if (auto plant = std::dynamic_pointer_cast<Plant>(obj)) {
            // 使用植物自身的碰撞检测方法
            if (plant->ContainsPoint(x, y)) {
                return plant;
            }
        }
    }
    return nullptr;
}

void GameWorld::AddPlant(int x, int y) {

    // 如果铲子被选中，则铲除植物而不是种植
    if (m_shovelSelected) {
        RemovePlant(x, y);
        return;
    }

    if (!m_selectedSeed) return;

    int price = m_selectedSeed->GetPrice();
    if (m_sunCount < price) return;

    std::shared_ptr<Plant> newPlant;
    switch (m_selectedSeed->GetPlantImageID()) {
    case ImageID::SUNFLOWER:
        newPlant = std::make_shared<Sunflower>(x, y, this);
        break;
    case ImageID::PEASHOOTER:
        newPlant = std::make_shared<Peashooter>(x, y, this);
        break;
    case ImageID::WALLNUT:
        newPlant = std::make_shared<Wallnut>(x, y, this);
        break;
    case ImageID::CHERRY_BOMB:
        newPlant = std::make_shared<CherryBomb>(x, y, this);
        break;
    case ImageID::REPEATER:
        newPlant = std::make_shared<Repeater>(x, y, this);
        break;
    default:
        return;
    }

    if (auto grid = GetGridAt(x, y)) {
        grid->SetPlant(newPlant);
        if (auto plant = dynamic_cast<Plant*>(newPlant.get())) {
            plant->SetWorld(this);
        }
    }

    // 成功种植植物后
    if (m_selectedSeed) {
        // 调用种子按钮的冷却开始
        m_selectedSeed->StartCooldown();
    }

    AddObject(newPlant);
    AddSun(-price);
    m_selectedSeed = nullptr;
}

// 生成一波僵尸
void GameWorld::GenerateWave() {
    m_waveCount++; // 增加波数计数

    // 计算本波僵尸数量
    int zombieCount = (15 + m_waveCount) / 10;

    // 计算僵尸类型概率
    int P1 = 20;
    int P2 = 2 * std::max(m_waveCount - 8, 0);
    int P3 = 3 * std::max(m_waveCount - 15, 0);
    int totalProb = P1 + P2 + P3;

    // 如果没有有效的概率，默认普通僵尸
    if (totalProb <= 0) {
        P1 = 1;
        totalProb = 1;
    }

    // 生成本波僵尸
    for (int i = 0; i < zombieCount; i++) {
        // 随机选择僵尸类型
        int randType = randInt(0, totalProb - 1);
        ZombieType type;

        if (randType < P1) {
            type = NORMAL_ZOMBIE;
        } else if (randType < P1 + P2) {
            type = POLE_VAULTING_ZOMBIE;
        } else {
            type = BUCKET_HEAD_ZOMBIE;
        }

        // 随机位置
        int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
        int row = randInt(0, GAME_ROWS - 1);
        int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

        // 创建僵尸对象
        std::shared_ptr<Zombie> zombie;
        switch (type) {
        case NORMAL_ZOMBIE:
            zombie = std::make_shared<NormalZombie>(x, y, this);
            break;
        case POLE_VAULTING_ZOMBIE:
            zombie = std::make_shared<PoleVaultingZombie>(x, y, this);
            break;
        case BUCKET_HEAD_ZOMBIE:
            zombie = std::make_shared<BucketHeadZombie>(x, y, this);
            break;
        }

        // 添加到游戏世界
        if (zombie) {
            AddObject(zombie);
        }
    }

    // 更新波数文本
    char waveBuffer[20];
    sprintf(waveBuffer, "Wave: %d", m_waveCount);
    m_waveText->SetText(waveBuffer);
}
