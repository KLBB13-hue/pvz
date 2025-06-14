#include "pvz/GameObject/SeedButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

SeedButton::SeedButton(ImageID imageID, int x, int y, int price,int cooldown,GameWorld* world)
    : GameObject(imageID, x, y, LayerID::UI, SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
    , m_world(world)
    , m_price(price)
    , m_cooldown(cooldown) {
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
    if (m_cooldownTimer > 0) {
        m_cooldownTimer--;

        if (m_cooldownTimer == 0 && m_cooldownMask) {
            m_cooldownMask->SetDead(true);
            m_cooldownMask = nullptr;
        }
    }
}

void SeedButton::OnClick() {
    if (IsCooling()) {
        return;
    }

    if (m_world->IsShovelSelected()) {
        m_world->SetShovelSelected(false);
        if (auto shovelButton = m_world->GetShovelButton()) {
            shovelButton->SetSelected(false);
        }
    }

    if (m_world->GetSelectedSeed() != this) {
        m_world->SetSelectedSeed(this);
    } else {
        m_world->SetSelectedSeed(nullptr);
    }
}

void SeedButton::StartCooldown() {
    m_cooldownTimer = m_cooldown;

    if (!m_cooldownMask) {
        m_cooldownMask = std::make_shared<CooldownMask>(GetX(), GetY());
        m_cooldownMask->SetSeedButton(this);
        m_world->AddObject(m_cooldownMask);
    }
}