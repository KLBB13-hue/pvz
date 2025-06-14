// Repeater.cpp
#include "pvz/GameObject/Repeater.hpp"
#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Repeater::Repeater(int x, int y, GameWorld* world)
    : ShooterPlant(ImageID::REPEATER, x, y, world, 300, 0) {}

void Repeater::Update() {
    ShooterPlant::Update();
    if (IsDead()) return;

    if (m_shouldShootSecond) {
        m_secondShotTimer--;
        if (m_secondShotTimer <= 0) {
            ShootSecond();
            m_shouldShootSecond = false;
        }
    }
}

void Repeater::CreateProjectile() {
    int peaX = GetX() + 30;
    int peaY = GetY() + 10;
    auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
    m_world->AddObject(pea);

    m_shouldShootSecond = true;
    m_secondShotTimer = 5;
    m_shootCooldown = 25;
}

void Repeater::ShootSecond() {
    int peaX = GetX() + 30;
    int peaY = GetY() + 10;
    auto pea = std::make_shared<Pea>(peaX, peaY, m_world);
    m_world->AddObject(pea);
}

