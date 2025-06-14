// CherryBomb.cpp
#include "pvz/GameObject/CherryBomb.hpp"
#include "pvz/GameObject/Explosion.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

CherryBomb::CherryBomb(int x, int y, GameWorld* world)
    : Plant(ImageID::CHERRY_BOMB, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, 4000),
      m_world(world) {}

void CherryBomb::Update() {
    Plant::Update();
    if (IsDead()) return;

    m_countdown--;
    if (m_countdown <= 0) {
        auto explosion = std::make_shared<Explosion>(GetX(), GetY(), m_world);
        m_world->AddObject(explosion);
        SetDead(true);
    }
}
