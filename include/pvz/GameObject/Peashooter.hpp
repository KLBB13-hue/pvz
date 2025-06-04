#ifndef PEASHOOTER_HPP__
#define PEASHOOTER_HPP__

#include "Plant.hpp"

class GameWorld; // 前置声明

class Peashooter : public Plant {
public:
    // 修改构造函数，添加 GameWorld* 参数
    Peashooter(int x, int y, GameWorld* world);

    // 添加 Update() 方法覆盖
    void Update() override;

private:
    GameWorld* m_world; // 添加指向 GameWorld 的指针
    int m_shootCooldown = 0; // 添加发射冷却计时器
};

#endif // !PEASHOOTER_HPP__