#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Pea::Pea(int x, int y, GameWorld* world)
    : GameObject(ImageID::PEA, x, y, LayerID::PROJECTILES, 20, 20, AnimID::NO_ANIMATION),
      m_world(world) {}

void Pea::Update() {
    MoveTo(GetX() + 8, GetY());

    if (GetX() > WINDOW_WIDTH) {
        SetDead(true);
    }

    m_world->CheckPeaCollisions(GetX(), GetY(), GetWidth(), GetHeight(), this);
}