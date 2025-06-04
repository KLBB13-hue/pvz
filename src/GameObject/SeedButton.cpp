#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

SeedButton::SeedButton(ImageID imageID, int x, int y, int price, GameWorld* world)
    : GameObject(imageID, x, y, LayerID::UI, SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
    , m_world(world)
    , m_price(price)
{
    // 映射种子图片ID到植物图片ID
    switch(imageID) {
    case ImageID::SEED_SUNFLOWER: m_plantImageID = ImageID::SUNFLOWER; break;
    case ImageID::SEED_PEASHOOTER: m_plantImageID = ImageID::PEASHOOTER; break;
    case ImageID::SEED_WALLNUT: m_plantImageID = ImageID::WALLNUT; break;
    case ImageID::SEED_CHERRY_BOMB: m_plantImageID = ImageID::CHERRY_BOMB; break;
    case ImageID::SEED_REPEATER: m_plantImageID = ImageID::REPEATER; break;
    default: m_plantImageID = ImageID::NONE;
    }
}

void SeedButton::OnClick() {
    // 如果铲子被选中，先取消铲子状态
    if (m_world->IsShovelSelected()) {
        // 添加调试输出
        std::cout << "Shovel active, deselecting shovel first" << std::endl;

        m_world->SetShovelSelected(false);
        if (auto shovelButton = m_world->GetShovelButton()) {
            shovelButton->SetSelected(false);
        }
    }

    // 原始种子选择逻辑
    if (m_world->GetSelectedSeed() != this) {
        m_world->SetSelectedSeed(this);
        // 使用 GetImageID() 方法
        std::cout << "Seed selected: " << static_cast<int>(GetImageID()) << std::endl;
    } else {
        m_world->SetSelectedSeed(nullptr);
        // 添加调试输出
        std::cout << "Seed deselected" << std::endl;
    }
}