#ifndef EXPLOSION_HPP__
#define EXPLOSION_HPP__

#include "pvz/GameObject/GameObject.hpp"

class GameWorld;

class Explosion : public GameObject {
public:
    Explosion(int x, int y, GameWorld* world);
    void Update() override;
    void CheckCollisionWithZombies();

private:
    GameWorld* m_world;
    int m_lifetime = 3; // 存在3帧
};

#endif // !EXPLOSION_HPP__
