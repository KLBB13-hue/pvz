#include "pvz/GameObject/Explosion.hpp"
#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp" // 包含网格尺寸常量

Explosion::Explosion(int x, int y, GameWorld* world)
    : GameObject(ImageID::EXPLOSION,
                x, y,
                LayerID::PROJECTILES,
                3 * LAWN_GRID_WIDTH, // 宽度为3个网格
                3 * LAWN_GRID_HEIGHT, // 高度为3个网格
                AnimID::NO_ANIMATION),
      m_world(world)
{
    // 构造函数完成
}

void Explosion::Update() {
    // 检查是否死亡
    if (IsDead()) {
        return;
    }

    // 检测与僵尸的碰撞
    CheckCollisionWithZombies();

    // 减少生命周期
    m_lifetime--;

    // 3帧后消失
    if (m_lifetime <= 0) {
        SetDead(true);
    }
}

void Explosion::CheckCollisionWithZombies() {
    const auto& objects = m_world->GetObjects();

    // 计算爆炸边界
    int expLeft = GetX() - GetWidth() / 2;
    int expRight = GetX() + GetWidth() / 2;
    int expTop = GetY() - GetHeight() / 2;
    int expBottom = GetY() + GetHeight() / 2;

    for (const auto& obj : objects) {
        if (obj->GetLayer() == LayerID::ZOMBIES && !obj->IsDead()) {
            // 计算僵尸边界
            int zombieLeft = obj->GetX() - obj->GetWidth() / 2;
            int zombieRight = obj->GetX() + obj->GetWidth() / 2;
            int zombieTop = obj->GetY() - obj->GetHeight() / 2;
            int zombieBottom = obj->GetY() + obj->GetHeight() / 2;

            // 检查碰撞
            if (expRight >= zombieLeft && expLeft <= zombieRight &&
                expBottom >= zombieTop && expTop <= zombieBottom) {
                // 立即杀死僵尸
                obj->SetDead(true);
                }
        }
    }
}
