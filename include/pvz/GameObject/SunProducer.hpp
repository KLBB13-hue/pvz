// SunProducer.hpp
#ifndef SUNPRODUCER_HPP__
#define SUNPRODUCER_HPP__

#include "Plant.hpp"

class SunProducer : public Plant {
public:
    SunProducer(ImageID imageID, int x, int y, GameWorld* world, int hp, int interval);

    void Update() override;

protected:
    virtual void GenerateSun();

    int m_sunTimer;
    int m_sunInterval;
    GameWorld* m_world;
};

#endif // !SUNPRODUCER_HPP__
