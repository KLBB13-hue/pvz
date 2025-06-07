#include "pvz/GameObject/CherryBomb.hpp"
#include "pvz/GameObject/Explosion.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

CherryBomb::CherryBomb(int x, int y, GameWorld* world)
    : Plant(ImageID::CHERRY_BOMB,
            x, y,
            LayerID::PLANTS,
            60,   // 宽度60
            80,   // 高度80
            AnimID::IDLE, 4000), // 4000点HP
      m_world(world)
{
    // 构造函数完成
}

void CherryBomb::Update() {
    // 检查是否死亡
    if (IsDead()) {
        return;
    }

    Plant::Update();

    // 减少倒计时
    m_countdown--;

    // 15帧后爆炸
    if (m_countdown <= 0) {
        // 创建爆炸特效
        auto explosion = std::make_shared<Explosion>(GetX(), GetY(), m_world);
        m_world->AddObject(explosion);

        // 樱桃炸弹死亡
        SetDead(true);
    }
}

