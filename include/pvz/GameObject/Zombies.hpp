/// Zombie.hpp
#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "pvz/GameObject/GameObject.hpp"

class Zombie : public GameObject {
public:
    Zombie(ImageID imageID, int x, int y, int width, int height,
           int health, GameWorld* world);

    void TakeDamage(int amount) override;

private:
    int m_health;
};

#endif // !ZOMBIE_HPP__
