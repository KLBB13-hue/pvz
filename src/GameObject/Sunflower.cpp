// Sunflower.cpp
#include "pvz/GameObject/Sunflower.hpp"

Sunflower::Sunflower(int x, int y, GameWorld* world)
    : SunProducer(ImageID::SUNFLOWER, x, y, world, 300, randInt(300, 450)) {}
