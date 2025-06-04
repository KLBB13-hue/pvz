#include "pvz/GameObject/Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer,
             int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID) {}

void Plant::Update() {}

void Plant::OnClick() {
    // 空实现，无铲子功能
}

GameWorld* Plant::GetWorld() const {
    return m_world;
}

void Plant::SetWorld(GameWorld* world) {
    m_world = world;
}