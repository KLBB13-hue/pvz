#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/Plant.hpp"

// 修改：使用 LAYER_UI 层级，尺寸设为 60x80
Grid::Grid(int x, int y, GameWorld* world)
    : GameObject(ImageID::NONE, x, y, LayerID::NEW,
                60, 80, AnimID::NO_ANIMATION), // 修改尺寸为 60x80
      m_world(world) {}

void Grid::OnClick() {
    if (m_world->IsShovelSelected()) {
        if (HasPlant()) {
            m_world->RemovePlant(GetX(), GetY());
            // 自动取消铲子状态
            m_world->SetShovelSelected(false);
            if (auto shovel = m_world->GetShovelButton()) {
                shovel->SetSelected(false);
            }
        }
        return; // 不执行种植逻辑
    }

    // 种植逻辑
    if (m_world->IsSeedSelected() && !HasPlant()) {
        m_world->AddPlant(GetX(), GetY());
    }
}