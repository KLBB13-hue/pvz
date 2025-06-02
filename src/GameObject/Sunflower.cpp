// Sunflower.cpp
#include "pvz/GameObject/Sunflower.hpp"
#include "pvz/utils.hpp"

Sunflower::Sunflower(int x, int y)
    : Plant(ImageID::SUNFLOWER,
            x,
            y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE) {
}

void Sunflower::Update() {
    // 向日葵的更新逻辑（后续可添加阳光生成）
}

void Sunflower::OnClick() {
    // 向日葵被点击时的处理
}
