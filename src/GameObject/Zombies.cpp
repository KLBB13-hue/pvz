#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, int width, int height,
               int health, GameWorld* world)
    : GameObject(imageID, x, y, LayerID::ZOMBIES, width, height, AnimID::WALK),
      m_health(health),
      m_world(world),
      m_width(width),
      m_height(height){
}

void Zombie::TakeDamage(int amount) {
    m_health -= amount;
    if (m_health <= 0) {
        SetDead(true);
    }
}

void Zombie::SetState(AnimID animID) {
    if (m_currentAnim != animID) {
        m_currentAnim = animID;
        PlayAnimation(animID);
    }
}

void Zombie::Update() {
    if (IsDead()) return;

    if (m_attackCooldown > 0) {
        m_attackCooldown--;
    }

    PerformAction();
}

void Zombie::Move() {
    MoveTo(GetX() - 1, GetY());
}

void Zombie::AttackPlant() {
    if (m_attackCooldown > 0) return;

    int gridX = GetX() - m_width / 2;
    int gridY = GetY();
    auto plant = m_world->GetPlantAt(gridX, gridY);

    if (plant) {
        plant->TakeDamage(3);
        m_attackCooldown = 1;
    }
}

