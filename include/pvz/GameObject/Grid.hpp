#ifndef GRID_HPP__
#define GRID_HPP__

#include "pvz/GameObject/GameObject.hpp"

// 前置声明 GameWorld
class GameWorld;

class Grid : public GameObject {
public:
    // 构造函数改为接收 GameWorld 指针
    Grid(int x, int y, GameWorld* world);
    virtual ~Grid() = default;

    void Update() override;
    void OnClick() override;

private:
    GameWorld* m_world; // 直接持有 GameWorld 指针
};

#endif // !GRID_HPP__
