// Peashooter.cpp
#include "pvz/GameObject/Peashooter.hpp"
#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Peashooter::Peashooter(int x, int y, GameWorld* world)
    : ShooterPlant(ImageID::PEASHOOTER, x, y, world, 300, 0) {}

void Peashooter::CreateProjectile() {
    int peaX = GetX() + 30;
    int peaY = GetY() + 10;
    auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
    m_world->AddObject(pea);
}