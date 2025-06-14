#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Grid::Grid(int x, int y, GameWorld* world)
    : GameObject(ImageID::NONE, x, y, LayerID::NEW, 60, 80, AnimID::NO_ANIMATION),
      m_world(world) {}

void Grid::OnClick() {
    if (m_world->IsShovelSelected()) {
        if (HasPlant()) {
            m_world->RemovePlant(GetX(), GetY());
            m_world->SetShovelSelected(false);
            if (auto shovel = m_world->GetShovelButton()) {
                shovel->SetSelected(false);
            }
        }
        return;
    }

    if (m_world->IsSeedSelected() && !HasPlant()) {
        m_world->AddPlant(GetX(), GetY());
    }
}