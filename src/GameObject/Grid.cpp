#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/Plant.hpp"

Grid::Grid(int x, int y, GameWorld* world)
    : GameObject(ImageID::NONE, x, y, LayerID::UI,
                 LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT,
                 AnimID::NO_ANIMATION),
      m_world(world) {}

void Grid::Update() {}

void Grid::OnClick() {
    if (m_world->IsSeedSelected()) {
        m_world->AddPlant(GetX(), GetY());
    }
}