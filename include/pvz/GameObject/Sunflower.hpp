// Sunflower.hpp
#ifndef SUNFLOWER_HPP__
#define SUNFLOWER_HPP__

#include "Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp" // 添加GameWorld引用

class Sunflower : public Plant {
public:
    Sunflower(int x, int y, GameWorld* world); // 添加world参数
    virtual ~Sunflower() = default;

    void Update() override;
    void OnClick() override;

private:
    GameWorld* m_world;   // 指向所属GameWorld
    int m_sunTimer;       // 阳光生成计时器
};

#endif // !SUNFLOWER_HPP__