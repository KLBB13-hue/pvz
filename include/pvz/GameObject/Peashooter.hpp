#ifndef PEASHOOTER_HPP__
#define PEASHOOTER_HPP__

#include "Plant.hpp"

class Peashooter : public Plant {
public:
    Peashooter(int x, int y, GameWorld* world);
};

#endif // !PEASHOOTER_HPP__