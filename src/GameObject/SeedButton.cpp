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
    // 点击事件将在GameWorld中统一处理
    // 暂时只设置选中的种子类型
    m_world->SetSelectedSeed(this);
}