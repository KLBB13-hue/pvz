#include "pvz/GameObject/Peashooter.hpp"
#include "pvz/GameObject/Pea.hpp" // 包含豌豆头文件
#include "pvz/GameWorld/GameWorld.hpp"
// 修改构造函数，添加 GameWorld* 参数
Peashooter::Peashooter(int x, int y, GameWorld* world)
    : Plant(ImageID::PEASHOOTER,
            x, y,
            LayerID::PLANTS,
            60,
            80,
            AnimID::IDLE,300),
      m_world(world), // 初始化 m_world
      m_shootCooldown(0) // 初始化冷却计时器
{
    // 构造函数完成
}

void Peashooter::Update() {
    // 步骤1: 检查是否死亡
    if (IsDead()) {
        return;
    }

    Plant::Update();

    // 步骤2: 处理冷却时间
    if (m_shootCooldown > 0) {
        m_shootCooldown--;
        return; // 冷却期间直接返回
    }

    // 步骤3: 检查右侧是否有僵尸
    bool zombieFound = false;
    const auto& objects = m_world->GetObjects();

    for (const auto& obj : objects) {
        if (obj->GetLayer() == LayerID::ZOMBIES && !obj->IsDead()) {
            // 检查是否在同一行 (Y坐标差小于40像素)
            int dy = abs(GetY() - obj->GetY());
            if (dy <= 40) {
                // 检查是否在右侧 (X坐标大于豌豆射手)
                if (obj->GetX() > GetX()) {
                    zombieFound = true;
                    break;
                }
            }
        }
    }

    if (zombieFound) {
        // 在右方30像素、上方20像素位置生成豌豆
        int peaX = GetX() + 30;
        int peaY = GetY() + 10;

        auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
        m_world->AddObject(pea);

        // 进入30 tick冷却时间
        m_shootCooldown = 30;
    }
}

