#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

SeedButton::SeedButton(ImageID imageID, int x, int y, int price,int cooldown,GameWorld* world)
    : GameObject(imageID, x, y, LayerID::UI, SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
    , m_world(world)
    , m_price(price)
    , m_cooldown(cooldown)

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


void SeedButton::Update() {
    // 更新冷却计时器
    if (m_cooldownTimer > 0) {
        m_cooldownTimer--;

        // 冷却结束时移除遮盖物
        if (m_cooldownTimer == 0 && m_cooldownMask) {
            m_cooldownMask->SetDead(true);
            m_cooldownMask = nullptr;
        }
    }
}

void SeedButton::OnClick() {
    // 如果正在冷却，则忽略点击
    if (IsCooling()) {
        return;
    }

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

void SeedButton::StartCooldown() {
    m_cooldownTimer = m_cooldown;

    // 创建冷却遮盖物
    if (!m_cooldownMask) {
        m_cooldownMask = std::make_shared<CooldownMask>(GetX(), GetY());
        m_cooldownMask->SetSeedButton(this); // 关联到当前种子按钮
        m_world->AddObject(m_cooldownMask);
    }
}