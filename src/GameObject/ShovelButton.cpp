#include "pvz/GameOBject/ShovelButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

ShovelButton::ShovelButton(int x, int y, GameWorld* world)
    : GameObject(ImageID::SHOVEL, x, y, LayerID::UI, 50, 50, AnimID::NO_ANIMATION)
    , m_world(world) {}

void ShovelButton::OnClick()
{
    // 如果已有选中的种子，则点击无效
    if (m_world->IsSeedSelected()) {
        return;
    }
}