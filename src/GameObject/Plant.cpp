#include "pvz/GameObject/Plant.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID) {
}

// 添加默认实现
void Plant::Update() {
    // 默认空实现
}

void Plant::OnClick() {
    // 默认空实现
}