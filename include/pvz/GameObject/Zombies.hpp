#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "pvz/GameObject/GameObject.hpp"

class GameWorld;

enum class ZombieType {
    NORMAL,
    POLE_VAULTING,
    BUCKET_HEAD
};

class Zombie : public GameObject {
public:
    Zombie(ImageID imageID, int x, int y, int width, int height,
           int health, GameWorld* world);
    virtual ~Zombie() = default;

    void TakeDamage(int amount);
    virtual void Update() override;

    AnimID GetState() const { return m_currentAnim; }
    void SetState(AnimID animID);

    void AttackPlant();

    ZombieType GetType() const { return m_type; }

    // 碰撞检测方法
    bool CheckCollision(int x, int y, int width, int height) const {
        const int zLeft = GetX() - GetWidth()/2;
        const int zRight = GetX() + GetWidth()/2;
        const int zTop = GetY() - GetHeight()/2;
        const int zBottom = GetY() + GetHeight()/2;

        return (x + width >= zLeft) && (x <= zRight) &&
               (y + height >= zTop) && (y <= zBottom);
    }

protected:
    virtual void PerformAction() = 0; // 纯虚函数，由子类实现

    void Move();

    ZombieType m_type;
    int m_health;
    GameWorld* m_world;
    int m_attackCooldown = 0;
    AnimID m_currentAnim = AnimID::WALK;

private:
    int m_width;
    int m_height;
};

#endif // ZOMBIE_HPP__

