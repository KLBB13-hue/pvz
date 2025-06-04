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

    // 初始化状态
    m_selectedSeed = nullptr;
    const int seedButtonY = WINDOW_HEIGHT - 44;
    int seedButtonX = 130;
    m_sunDropTimer = 180;

    // 向日葵种子
    AddObject(std::make_shared<SeedButton>(
        ImageID::SEED_SUNFLOWER,
        seedButtonX, seedButtonY,
        50, this
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

    auto it = m_gameObjects.begin();
    while (it != m_gameObjects.end()) {
        auto& obj = *it;
        if (obj->IsDead()) {
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

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
    m_gameObjects.clear();
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

void GameWorld::AddPlant(int x, int y) {
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

    AddObject(newPlant);
    AddSun(-price);
    m_selectedSeed = nullptr;
}


