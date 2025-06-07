#ifndef PEA_HPP__
#define PEA_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class GameWorld; // 前置声明

class Pea : public GameObject {
public:
    Pea(int x, int y, GameWorld* world);
    void Update() override;
    void OnClick() override {} // 空实现
    bool CheckCollisionWithZombies();

private:
    GameWorld* m_world; // 用于访问游戏世界

};

#endif // !PEA_HPP__
