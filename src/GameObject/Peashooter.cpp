#include "pvz/GameObject/Peashooter.hpp"
#include "pvz/GameObject/Pea.hpp" // 包含豌豆头文件
#include "pvz/GameWorld/GameWorld.hpp"
// 修改构造函数，添加 GameWorld* 参数
Peashooter::Peashooter(int x, int y, GameWorld* world)
    : Plant(ImageID::PEASHOOTER,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,300),
      m_world(world), // 初始化 m_world
      m_shootCooldown(0) // 初始化冷却计时器
{
    // 构造函数完成
}

// 添加 Update() 方法实现
void Peashooter::Update() {
    Plant::Update(); // 调用基类更新

    // 发射冷却计时
    if (m_shootCooldown > 0) {
        m_shootCooldown--;
    }

    // 冷却结束，发射豌豆
    if (m_shootCooldown <= 0) {
        // 在豌豆射手右侧创建豌豆
        int peaX = GetX() + GetWidth()/2 + 20; // 豌豆射手右侧
        int peaY = GetY() + GetHeight()/2 - 30;

        // 创建豌豆对象
        auto pea = std::make_shared<Pea>(peaX, peaY, m_world);

        // 添加到游戏世界
        m_world->AddObject(pea);

        // 重置冷却时间（约3秒）
        m_shootCooldown = 30;
    }
}