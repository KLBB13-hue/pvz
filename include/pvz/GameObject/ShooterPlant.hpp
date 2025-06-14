// ShooterPlant.hpp
#ifndef SHOOTERPLANT_HPP__
#define SHOOTERPLANT_HPP__

#include "Plant.hpp"

class ShooterPlant : public Plant {
public:
    ShooterPlant(ImageID imageID, int x, int y, GameWorld* world, int hp, int cooldown);

    virtual void Update() override;

protected:
    virtual void CreateProjectile() = 0;

    GameWorld* m_world;
    int m_shootCooldown;

    bool CheckZombiesInLane();
};

#endif // !SHOOTERPLANT_HPP__