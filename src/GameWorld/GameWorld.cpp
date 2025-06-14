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
#include "pvz/GameObject/SpecificZombies.hpp"

void GameWorld::Init() {
    // 创建游戏背景
    auto background = std::make_shared<Background>(
        ImageID::BACKGROUND,
        WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
        LayerID::BACKGROUND,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        AnimID::NO_ANIMATION
    );
    AddObject(background);

    // 初始化网格系统
    m_grids.clear();
    for (int row = 0; row < GAME_ROWS; row++) {
        for (int col = 0; col < GAME_COLS; col++) {
            int x = FIRST_COL_CENTER + col * LAWN_GRID_WIDTH;
            int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

            auto grid = std::make_shared<Grid>(x, y, this);
            AddObject(grid);
            m_grids.push_back(grid);
        }
    }

    // 创建UI元素
    m_sunText = std::make_shared<TextBase>(
        50, WINDOW_HEIGHT - 78,
        "50",
        0.0, 0.0, 0.0,
        false
    );

    m_waveText = std::make_shared<TextBase>(
        WINDOW_WIDTH - 160,
        8,
        "Wave: 0",
        0.0, 0.0, 0.0,
        true
    );

    // 初始化游戏状态
    m_selectedSeed = nullptr;
    const int seedButtonY = WINDOW_HEIGHT - 44;
    int seedButtonX = 130;
    m_sunDropTimer = 180;

    // 创建种子按钮
    // 向日葵
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_SUNFLOWER,
        seedButtonX, seedButtonY,
        50, 240, this
    ));

    // 豌豆射手
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_PEASHOOTER,
        seedButtonX, seedButtonY,
        100, 240, this
    ));

    // 坚果墙
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_WALLNUT,
        seedButtonX, seedButtonY,
        50, 900, this
    ));

    // 樱桃炸弹
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_CHERRY_BOMB,
        seedButtonX, seedButtonY,
        150, 1200, this
    ));

    // 双发射手
    seedButtonX += 60;
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_REPEATER,
        seedButtonX, seedButtonY,
        200, 240, this
    ));

    // 铲子按钮
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
    // 更新阳光计数
    char buffer[20];
    sprintf(buffer, "%d", m_sunCount);
    m_sunText->SetText(buffer);

    // 处理波次逻辑
    if (m_nextWaveTimer > 0) {
        m_nextWaveTimer--;
        if (m_nextWaveTimer == 0) {
            GenerateWave();
        }
    }

    // 检查失败条件
    bool zombieReached = false;
    for (auto& obj : m_gameObjects) {
        auto zombie = std::dynamic_pointer_cast<Zombie>(obj);
        if (zombie && zombie->GetX() < 0) {
            zombieReached = true;
            break;
        }
    }

    if (zombieReached) {
        // 游戏结束界面
        auto zombiesWonImage = std::make_shared<Background>(
            ImageID::ZOMBIES_WON,
            WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
            LayerID::UI,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            AnimID::NO_ANIMATION
        );
        AddObject(zombiesWonImage);

        // 显示波数
        auto waveNumText = std::make_shared<TextBase>(
            330,
            50,
            std::to_string(m_waveCount - 1),
            1.0, 1.0, 1.0,
            true
        );
        AddText(waveNumText);

        return LevelStatus::LOSING;
    }

    // 更新游戏对象
    auto it = m_gameObjects.begin();
    while (it != m_gameObjects.end()) {
        if ((*it)->IsDead()) {
            // 清理网格关联
            if (auto plant = dynamic_cast<Plant*>((*it).get())) {
                for (auto& grid : m_grids) {
                    if (grid->GetPlant().get() == plant) {
                        grid->SetPlant(nullptr);
                    }
                }
            }
            it = m_gameObjects.erase(it);
        } else {
            (*it)->Update();
            ++it;
        }
    }

    // 生成阳光
    m_sunDropTimer--;
    if (m_sunDropTimer <= 0) {
        int sunX = randInt(75, WINDOW_WIDTH - 75);
        int sunY = WINDOW_HEIGHT - 1;
        auto sun = std::make_shared<Sun>(sunX, sunY, Sun::FALLING_SUN, this);
        AddObject(sun);
        m_sunDropTimer = 300;
    }

    // 更新铲子状态
    if (m_shovelButton) {
        m_shovelSelected = m_shovelButton->IsSelected();
    }

    // 确保状态互斥
    if (m_selectedSeed != nullptr && m_shovelSelected) {
        SetShovelSelected(false);
        if (m_shovelButton) {
            m_shovelButton->SetSelected(false);
        }
    }

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
    m_gameObjects.clear();
    m_grids.clear();
    m_selectedSeed = nullptr;
    m_sunCount = 50;
    m_waveCount = 0;
    m_nextWaveTimer = 1200;
    m_sunDropTimer = 180;
    m_shovelSelected = false;
    m_sunText.reset();
    m_waveText.reset();
    m_shovelButton.reset();
}

std::shared_ptr<Grid> GameWorld::GetGridAt(int x, int y) {
    for (auto& grid : m_grids) {
        int gridLeft = grid->GetX() - LAWN_GRID_WIDTH / 2;
        int gridRight = grid->GetX() + LAWN_GRID_WIDTH / 2;
        int gridTop = grid->GetY() - LAWN_GRID_HEIGHT / 2;
        int gridBottom = grid->GetY() + LAWN_GRID_HEIGHT / 2;

        if (x >= gridLeft && x <= gridRight &&
            y >= gridTop && y <= gridBottom) {
            return grid;
        }
    }
    return nullptr;
}

void GameWorld::RemovePlant(int x, int y) {
    if (auto grid = GetGridAt(x, y)) {
        if (auto plant = grid->GetPlant()) {
            plant->SetDead(true);
            grid->SetPlant(nullptr);

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
        if (auto plant = std::dynamic_pointer_cast<Plant>(obj)) {
            if (plant->ContainsPoint(x, y)) {
                return plant;
            }
        }
    }
    return nullptr;
}

void GameWorld::AddPlant(int x, int y) {
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

    if (m_selectedSeed) {
        m_selectedSeed->StartCooldown();
    }

    AddObject(newPlant);
    AddSun(-price);
    m_selectedSeed = nullptr;
}

void GameWorld::GenerateWave() {
    m_waveCount++;
    int zombieCount = (15 + m_waveCount) / 10;

    // 输出调试信息
    std::cout << "第 " << m_waveCount << " 波开始，生成 " << zombieCount << " 个普通僵尸\n";

    for (int i = 0; i < zombieCount; i++) {
        int x = WINDOW_WIDTH - 40;
        int row = randInt(0, GAME_ROWS - 1);
        int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

        auto zombie = std::make_shared<NormalZombie>(x, y, this);
        AddObject(zombie);
    }

    // 更新波数显示
    char waveBuffer[20];
    sprintf(waveBuffer, "Wave: %d", m_waveCount);
    if (m_waveText) {
        m_waveText->SetText(waveBuffer);
    }

    // 计算下一波时间
    int nextInterval = 600 - 20 * m_waveCount;
    if (nextInterval < 150) nextInterval = 150;
    m_nextWaveTimer = nextInterval;

    std::cout << "下一波将在 " << nextInterval << " 帧后到来\n";
}

bool GameWorld::HasZombieInLane(int plantX, int plantY) const {
    for (const auto& obj : m_gameObjects) {
        if (obj->GetLayer() != LayerID::ZOMBIES || obj->IsDead()) continue;

        int dy = std::abs(plantY - obj->GetY());
        if (dy <= 40 && obj->GetX() > plantX) {
            return true;
        }
    }
    return false;
}

void GameWorld::HandleExplosion(int x, int y, int width, int height) {
    const int expLeft = x - width/2;
    const int expRight = x + width/2;
    const int expTop = y - height/2;
    const int expBottom = y + height/2;

    for (auto& obj : m_gameObjects) {
        if (obj->GetLayer() != LayerID::ZOMBIES || obj->IsDead()) continue;

        const int zLeft = obj->GetX() - obj->GetWidth()/2;
        const int zRight = obj->GetX() + obj->GetWidth()/2;
        const int zTop = obj->GetY() - obj->GetHeight()/2;
        const int zBottom = obj->GetY() + obj->GetHeight()/2;

        if (expRight >= zLeft && expLeft <= zRight &&
            expBottom >= zTop && expTop <= zBottom)
        {
            obj->SetDead(true);
        }
    }
}

void GameWorld::CheckPeaCollisions(int peaX, int peaY, int peaWidth, int peaHeight, Pea* pea) {
    const int peaLeft = peaX - peaWidth / 2;
    const int peaRight = peaX + peaWidth / 2;
    const int peaTop = peaY - peaHeight / 2;
    const int peaBottom = peaY + peaHeight / 2;

    for (auto& obj : m_gameObjects) {
        if (obj->GetLayer() != LayerID::ZOMBIES || obj->IsDead()) continue;

        auto zombie = std::dynamic_pointer_cast<Zombie>(obj);
        if (!zombie) continue;

        if (zombie->CheckCollision(peaLeft, peaTop, peaRight - peaLeft, peaBottom - peaTop)) {
            zombie->TakeDamage(20);
            pea->SetDead(true);
            return;
        }
    }
}

void GameWorld::CheckPeaCollisions(int peaX, int peaY, int peaWidth, int peaHeight, std::shared_ptr<Pea> pea) {
    CheckPeaCollisions(peaX, peaY, peaWidth, peaHeight, pea.get());
}