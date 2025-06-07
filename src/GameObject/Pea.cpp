#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Zombies.hpp" // 假设有Zombie类
#include <climits> // 用于INT_MAX

Pea::Pea(int x, int y, GameWorld* world)
    : GameObject(ImageID::PEA,
                x, y,
                LayerID::PROJECTILES,
                28, 28,
                AnimID::NO_ANIMATION),
      m_world(world)
{
    // 初始化完成
}

void Pea::Update() {
    // 步骤1: 检查是否死亡
    if (IsDead()) {
        return;
    }

    // 步骤2: 向右移动8像素
    MoveTo(GetX() + 8, GetY());

    // 步骤3: 检查是否飞出屏幕
    if (GetX() >= WINDOW_WIDTH) {
        SetDead(true);
        return;
    }

    // 步骤4: 检测与僵尸的碰撞
    if (CheckCollisionWithZombies()) {
        SetDead(true); // 碰撞后豌豆立即死亡
    }
}

bool Pea::CheckCollisionWithZombies() {
    const auto& objects = m_world->GetObjects();
    bool collisionOccurred = false;

    for (const auto& obj : objects) {
        if (obj->GetLayer() == LayerID::ZOMBIES && !obj->IsDead()) {
            // 计算碰撞边界
            int peaLeft = GetX() - GetWidth() / 2;
            int peaRight = GetX() + GetWidth() / 2;
            int peaTop = GetY() - GetHeight() / 2;
            int peaBottom = GetY() + GetHeight() / 2;

            int zombieLeft = obj->GetX() - obj->GetWidth() / 2;
            int zombieRight = obj->GetX() + obj->GetWidth() / 2;
            int zombieTop = obj->GetY() - obj->GetHeight() / 2;
            int zombieBottom = obj->GetY() + obj->GetHeight() / 2;

            // 检查碰撞
            if (peaRight >= zombieLeft && peaLeft <= zombieRight &&
                peaBottom >= zombieTop && peaTop <= zombieBottom) {
                // 对僵尸造成20点伤害
                if (auto zombie = dynamic_cast<Zombie*>(obj.get())) {
                    zombie->TakeDamage(20);
                }
                collisionOccurred = true;
                }
        }
    }

    return collisionOccurred;
}