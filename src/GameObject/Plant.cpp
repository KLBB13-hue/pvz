#include "pvz/GameObject/Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer,
             int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID),
      m_hp(hp) {}

void Plant::Update() {}

void Plant::OnClick() {}

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

bool Plant::ContainsPoint(int x, int y) const {
    int left = GetX() - GetWidth() / 2;
    int right = GetX() + GetWidth() / 2;
    int top = GetY() - GetHeight() / 2;
    int bottom = GetY() + GetHeight() / 2;
    return (x >= left && x <= right && y >= top && y <= bottom);
}