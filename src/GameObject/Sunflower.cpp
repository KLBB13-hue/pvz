// Sunflower.cpp
#include "pvz/GameObject/Sunflower.hpp"
#include "pvz/utils.hpp"
#include <iostream>

Sunflower::Sunflower(int x, int y)
    : Plant(ImageID::SUNFLOWER,
            x,
            y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE) {
    std::cout << "向日葵种植在 (" << x << ", " << y << ")\n";
}

void Sunflower::Update() {
    // 向日葵的更新逻辑（后续可添加阳光生成）
}

void Sunflower::OnClick() {
    // 向日葵被点击时的处理
}
