#ifndef SPECIFIC_ZOMBIES_HPP
#define SPECIFIC_ZOMBIES_HPP

#include "pvz/GameObject/Zombies.hpp"

class NormalZombie : public Zombie {
public:
    NormalZombie(int x, int y, GameWorld* world);
    void Update() override; // 添加Update方法声明
};

class PoleVaultingZombie : public Zombie {
public:
    PoleVaultingZombie(int x, int y, GameWorld* world);
    void Update() override; // 添加Update方法声明
};

class BucketHeadZombie : public Zombie {
public:
    BucketHeadZombie(int x, int y, GameWorld* world);
    void Update() override; // 添加Update方法声明
};

#endif // SPECIFIC_ZOMBIES_HPP
