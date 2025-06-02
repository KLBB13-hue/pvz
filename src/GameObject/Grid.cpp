#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameWorld/GameWorld.hpp" // 包含 GameWorld 头文件
#include "pvz/utils.hpp"

Grid::Grid(int x, int y, GameWorld* world)
    : GameObject(ImageID::NONE,
                x,
                y,
                LayerID::UI,
                LAWN_GRID_WIDTH,
                LAWN_GRID_HEIGHT,
                AnimID::NO_ANIMATION),
      m_world(world) {
}

void Grid::Update() {
    // 种植位不需要每帧更新
}

void Grid::OnClick() {
    if (m_world) {
        // 直接调用 GameWorld 的方法
        m_world->AddPlant(GetX(), GetY());
    }
}