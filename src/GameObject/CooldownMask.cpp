#include "pvz/GameObject/CooldownMask.hpp"
#include "pvz/GameObject/SeedButton.hpp"

CooldownMask::CooldownMask(int x, int y)
    : GameObject(ImageID::COOLDOWN_MASK,
                 x, y,
                 LayerID::COOLDOWNMASK,
                 50, 70,
                 AnimID::NO_ANIMATION)
{
}

void CooldownMask::Update() {
    // 检查关联的种子按钮是否结束冷却
    if (m_seedButton && !m_seedButton->IsCooling()) {
        SetDead(true); // 冷却结束，移除遮盖物
    }
}

bool CooldownMask::CanBeClicked(int x, int y) const {
    // 永远返回false，使冷却遮盖物不可点击
    return false;
}