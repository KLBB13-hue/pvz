#include "pvz/GameObject/Repeater.hpp"
#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Repeater::Repeater(int x, int y, GameWorld* world)
    : Plant(ImageID::REPEATER,
            x, y,
            LayerID::PLANTS,
            60,   // 宽度60
            80,   // 高度80
            AnimID::IDLE, 300), // ANIMID_IDLE_ANIM和300点HP
      m_world(world)
{
    // 构造函数完成
}

void Repeater::Update() {
    // 步骤1: 检查是否死亡
    if (IsDead()) {
        return;
    }

    Plant::Update();

    // 处理第二发豌豆
    if (m_shouldShootSecond) {
        m_secondShotTimer--;
        if (m_secondShotTimer <= 0) {
            // 发射第二发豌豆
            int peaX = GetX() + 30;
            int peaY = GetY() + 10;

            auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
            m_world->AddObject(pea);

            m_shouldShootSecond = false;
        }
    }

    // 处理冷却时间
    if (m_shootCooldown > 0) {
        m_shootCooldown--;
        return;
    }

    // 检查右侧是否有僵尸
    bool zombieFound = false;
    const auto& objects = m_world->GetObjects();

    for (const auto& obj : objects) {
        if (obj->GetLayer() == LayerID::ZOMBIES && !obj->IsDead()) {
            // 检查是否在同一行 (Y坐标差小于40像素)
            int dy = abs(GetY() - obj->GetY());
            if (dy <= 40) {
                // 检查是否在右侧 (X坐标大于双发射手位置)
                if (obj->GetX() > GetX()) {
                    zombieFound = true;
                    break;
                }
            }
        }
    }

    if (zombieFound) {
        // 发射第一发豌豆
        int peaX = GetX() + 30;
        int peaY = GetY() + 10;

        auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
        m_world->AddObject(pea);

        // 设置第二发豌豆定时器
        m_shouldShootSecond = true;
        m_secondShotTimer = 5; // 5 tick后发射第二发

        // 设置冷却时间（25tick + 5tick = 30tick）
        m_shootCooldown = 25;
    }
}

