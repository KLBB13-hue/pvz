// Repeater.hpp
#ifndef REPEATER_HPP__
#define REPEATER_HPP__

#include "pvz/GameObject/ShooterPlant.hpp"

class Repeater : public ShooterPlant {
public:
    Repeater(int x, int y, GameWorld* world);
    void Update() override;

private:
    void CreateProjectile() override;
    void ShootSecond();

    int m_secondShotTimer = 0;
    bool m_shouldShootSecond = false;
};

#endif // !REPEATER_HPP__