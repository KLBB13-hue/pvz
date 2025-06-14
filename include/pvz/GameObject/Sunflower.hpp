// Sunflower.hpp
#ifndef SUNFLOWER_HPP__
#define SUNFLOWER_HPP__

#include "pvz/GameObject/SunProducer.hpp"

class Sunflower : public SunProducer {
public:
    Sunflower(int x, int y, GameWorld* world);
};

#endif // !SUNFLOWER_HPP__