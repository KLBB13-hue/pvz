// Grid.cpp
#include "pvz/GameObject/Grid.hpp"
#include "pvz/utils.hpp"

Grid::Grid(int x, int y, ClickCallback callback)
    : GameObject(ImageID::NONE,  // 使用NONE表示无贴图
                x,
                y,
                LayerID::UI,     // 放在UI层确保可点击
                LAWN_GRID_WIDTH,
                LAWN_GRID_HEIGHT,
                AnimID::NO_ANIMATION),
      m_callback(callback) {
}

void Grid::Update() {
    // 种植位不需要每帧更新
}

void Grid::OnClick() {
    if (m_callback) {
        m_callback(GetX(), GetY());
    }
}