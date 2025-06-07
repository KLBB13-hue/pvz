#ifndef REPEATER_HPP__
#define REPEATER_HPP__

#include "Plant.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

class Repeater : public Plant {
public:
    Repeater(int x, int y, GameWorld* world);
    void Update() override;

private:
    GameWorld* m_world;
    int m_shootCooldown = 0;
    int m_secondShotTimer = 0;
    bool m_shouldShootSecond = false;
};

#endif // !REPEATER_HPP__