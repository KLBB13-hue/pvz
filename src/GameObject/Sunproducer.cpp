// SunProducer.cpp
#include "pvz/GameObject/SunProducer.hpp"
#include "pvz/GameObject/Sun.hpp"

SunProducer::SunProducer(ImageID imageID, int x, int y, GameWorld* world, int hp, int interval)
    : Plant(imageID, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, hp),
      m_world(world),
      m_sunTimer(interval),
      m_sunInterval(interval) {}

void SunProducer::Update() {
    Plant::Update();
    if (IsDead()) return;

    if (--m_sunTimer <= 0) {
        GenerateSun();
        m_sunTimer = m_sunInterval;
    }
}

void SunProducer::GenerateSun() {
    int sunX = GetX();
    int sunY = GetY() - 50;
    auto sun = std::make_shared<Sun>(sunX, sunY, Sun::SUNFLOWER_SUN, m_world);
    m_world->AddObject(sun);
}