// Sunflower.cpp
#include "pvz/GameObject/Sunflower.hpp"
#include "pvz/GameObject/Sun.hpp" // 添加Sun引用
#include "pvz/utils.hpp"
#include <iostream>

Sunflower::Sunflower(int x, int y, GameWorld* world)
    : Plant(ImageID::SUNFLOWER,
            x,
            y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,300),
      m_world(world),
      m_sunTimer(randInt(300, 450)) { // 随机初始计时器(10-15秒)
    std::cout << "向日葵种植在 (" << x << ", " << y << ")\n";
}

void Sunflower::Update() {
    if (IsDead()) return;

    // 阳光生成逻辑
    if (--m_sunTimer <= 0) {
        // 在向日葵上方生成阳光
        int sunX = GetX();
        int sunY = GetY() - 50;

        // 创建向日葵产生的阳光
        auto sun = std::make_shared<Sun>(
            sunX, sunY,
            Sun::SUNFLOWER_SUN,
            m_world
        );

        m_world->AddObject(sun);
        m_sunTimer = randInt(300, 450); // 重置计时器(10-15秒)
    }
}

void Sunflower::OnClick() {
    // 向日葵被点击时的处理
}
