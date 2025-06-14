#include "pvz/GameObject/Explosion.hpp"
#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

Explosion::Explosion(int x, int y, GameWorld* world)
    : GameObject(ImageID::EXPLOSION,
                x, y,
                LayerID::PROJECTILES,
                3 * LAWN_GRID_WIDTH,
                3 * LAWN_GRID_HEIGHT,
                AnimID::NO_ANIMATION),
      m_world(world) {}

void Explosion::Update() {
    if (IsDead()) {
        return;
    }

    CheckCollisionWithZombies();

    m_lifetime--;

    if (m_lifetime <= 0) {
        SetDead(true);
    }
}

void Explosion::CheckCollisionWithZombies() {
    m_world->HandleExplosion(GetX(), GetY(), GetWidth(), GetHeight());
}