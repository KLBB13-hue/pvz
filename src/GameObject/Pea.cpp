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
    // 获取游戏世界中的所有对象
    const auto& objects = m_world->GetObjects();
    std::shared_ptr<GameObject> targetZombie = nullptr; // 目标僵尸（最左侧）
    int minX = INT_MAX; // 记录最左侧的x坐标

    for (const auto& obj : objects) {
        // 只检查存活的僵尸对象
        if (obj->GetLayer() == LayerID::ZOMBIES && !obj->IsDead()) {
            // 计算两对象中心点的距离
            int dx = abs(GetX() - obj->GetX());
            int dy = abs(GetY() - obj->GetY());

            // 计算碰撞所需的最小距离
            int min_dist_x = (GetWidth() + obj->GetWidth()) / 2;
            int min_dist_y = (GetHeight() + obj->GetHeight()) / 2;

            // 检测碰撞（中心和边缘距离都需满足条件）
            if (dx < min_dist_x && dy < min_dist_y) {
                // 找到最左侧的僵尸
                if (obj->GetX() < minX) {
                    minX = obj->GetX();
                    targetZombie = obj;
                }
            }
        }
    }

    // 如果找到碰撞目标
    if (targetZombie) {
        // 对僵尸造成伤害
        auto zombie = dynamic_cast<Zombie*>(targetZombie.get());
        if (zombie) {
            zombie->TakeDamage(20);
        }
        return true;  // 发生碰撞
    }

    return false;  // 未发生碰撞
}