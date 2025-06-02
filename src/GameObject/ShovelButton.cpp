#include "pvz/GameOBject/ShovelButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

ShovelButton::ShovelButton(int x, int y, GameWorld* world)
    : GameObject(ImageID::SHOVEL, x, y, LayerID::UI, 50, 50, AnimID::NO_ANIMATION)
    , m_world(world) {}

void ShovelButton::OnClick() {
    // 切换铲子选中状态
    m_world->SetShovelSelected(!m_world->IsShovelSelected());
}