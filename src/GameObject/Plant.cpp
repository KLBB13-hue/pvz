#include "pvz/GameObject/Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer,
             int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID), m_hp(hp){}

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

int Plant::GetHP() const {
    return m_hp;
}

void Plant::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        SetDead(true);
    }
}