// ShooterPlant.cpp
#include "pvz/GameObject/ShooterPlant.hpp"
#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
ShooterPlant::ShooterPlant(ImageID imageID, int x, int y, GameWorld* world, int hp, int cooldown)
    : Plant(imageID, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, hp),
      m_world(world),
      m_shootCooldown(cooldown) {}

void ShooterPlant::Update() {
    Plant::Update();
    if (IsDead()) return;

    if (m_shootCooldown > 0) {
        m_shootCooldown--;
        return;
    }

    if (CheckZombiesInLane()) {
        CreateProjectile();
        m_shootCooldown = 30;
    }
}

bool ShooterPlant::CheckZombiesInLane() {
    return m_world->HasZombieInLane(GetX(), GetY());
}