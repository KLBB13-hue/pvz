/// Zombie.hpp
#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "pvz/GameObject/GameObject.hpp"

class GameWorld;

enum ZombieType {
    NORMAL_ZOMBIE,
    POLE_VAULTING_ZOMBIE,
    BUCKET_HEAD_ZOMBIE
};

// 新增：僵尸行为状态枚举
enum class ZombieState {
    WALKING,
    EATING
};

class Zombie : public GameObject {
public:
    Zombie(ImageID imageID, int x, int y, int width, int height,
           int health, GameWorld* world);
    virtual ~Zombie() = default;

    void TakeDamage(int amount);
    virtual void Update() override;

    // 使用 AnimID 表示状态
    AnimID GetState() const { return m_currentAnim; }
    AnimID SetState(AnimID animID) { return m_currentAnim = animID; }

    // 攻击植物的方法
    void AttackPlant();

protected:
    int m_health;
    GameWorld* m_world;
    int m_attackCooldown = 0; // 攻击冷却计时器
    AnimID m_currentAnim ;
};

#endif // ZOMBIE_HPP__


