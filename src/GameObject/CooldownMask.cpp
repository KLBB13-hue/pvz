#include "pvz/GameObject/CooldownMask.hpp"
#include "pvz/GameObject/SeedButton.hpp"

CooldownMask::CooldownMask(int x, int y)
    : GameObject(ImageID::COOLDOWN_MASK,
                 x, y,
                 LayerID::COOLDOWNMASK,
                 50, 70,
                 AnimID::NO_ANIMATION) {}

void CooldownMask::Update() {
    if (m_seedButton && !m_seedButton->IsCooling()) {
        SetDead(true);
    }
}

bool CooldownMask::CanBeClicked(int x, int y) const {
    return false;
}