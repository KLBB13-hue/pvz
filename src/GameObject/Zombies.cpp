#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameObject/Plant.hpp" // 添加Plant头文件
#include "pvz/GameWorld/GameWorld.hpp"



Zombie::Zombie(ImageID imageID, int x, int y, int width, int height,
               int health, GameWorld* world)
    : GameObject(imageID, x, y, LayerID::ZOMBIES, width, height, AnimID::WALK),
      m_health(health),
      m_world(world),
    m_currentAnim(AnimID::WALK)
{
    // 构造函数
}

void Zombie::TakeDamage(int amount) {
    m_health -= amount;
    if (m_health <= 0) {
        SetDead(true);
    }
}

void Zombie::Update() {
    // 如果已经死亡，直接返回
    if (IsDead()) {
        return;
    }

    // 攻击冷却计时
    if (m_attackCooldown > 0) {
        m_attackCooldown--;
    }
}

void Zombie::AttackPlant() {
    if (m_attackCooldown > 0) return;

    // 使用与NormalZombie一致的检测位置
    int gridX = GetX() - GetWidth()/2;
    int gridY = GetY();
    auto plant = m_world->GetPlantAt(gridX, gridY);

    if (plant) {
        plant->TakeDamage(3);
        m_attackCooldown = 1;
    }
}


