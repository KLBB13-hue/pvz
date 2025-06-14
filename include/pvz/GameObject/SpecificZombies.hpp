#ifndef SPECIFIC_ZOMBIES_HPP
#define SPECIFIC_ZOMBIES_HPP

#include "pvz/GameObject/Zombies.hpp"

class NormalZombie : public Zombie {
public:
    NormalZombie(int x, int y, GameWorld* world);
    void PerformAction() override;
};

class PoleVaultingZombie : public Zombie {
public:
    PoleVaultingZombie(int x, int y, GameWorld* world);
    void PerformAction() override;

private:
    bool m_hasPole = true;
};

class BucketHeadZombie : public Zombie {
public:
    BucketHeadZombie(int x, int y, GameWorld* world);
    void PerformAction() override;
};

#endif // SPECIFIC_ZOMBIES_HPP
