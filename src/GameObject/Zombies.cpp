// Zombie.cpp
#include "pvz/GameObject/Zombies.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, int width, int height,
               int health, GameWorld* world)
    : GameObject(imageID, x, y, LayerID::ZOMBIES, width, height, AnimID::WALK),
      m_health(health)
{
    // 构造函数
}

void Zombie::TakeDamage(int amount) {
    m_health -= amount;
    if (m_health <= 0) {
        SetDead(true);
    }
}