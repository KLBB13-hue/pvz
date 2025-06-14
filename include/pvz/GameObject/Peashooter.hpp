// Peashooter.hpp
#ifndef PEASHOOTER_HPP__
#define PEASHOOTER_HPP__

#include "pvz/GameObject/ShooterPlant.hpp"

class Peashooter : public ShooterPlant {
public:
    Peashooter(int x, int y, GameWorld* world);

protected:
    void CreateProjectile() override;
};

#endif // !PEASHOOTER_HPP__