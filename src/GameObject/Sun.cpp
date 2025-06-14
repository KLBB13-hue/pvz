// Sun.cpp
#include "pvz/GameObject/Sun.hpp"
#include "pvz/utils.hpp"

Sun::Sun(int x, int y, SunType type, GameWorld* world)
    : GameObject(ImageID::SUN, x, y, LayerID::SUN , 80, 80, AnimID::IDLE),
      m_type(type),
      m_state(0),
      m_countdown(0),
      m_vy(0),
      m_landedTime(0),
      m_world(world) {

    if (type == FALLING_SUN) {
        m_countdown = randInt(63, 263);
    } else {
        m_countdown = 12;
        m_vy = -4;
    }
}

void Sun::Update() {
    if (m_state == 0) {
        if (m_type == FALLING_SUN) {
            MoveTo(GetX(), GetY() - 2);
        } else {
            MoveTo(GetX() + 2, GetY() - m_vy);
            m_vy += 1;
        }

        m_countdown--;
        if (m_countdown <= 0) {
            m_state = 1;
            m_landedTime = 0;
        }
    } else {
        m_landedTime++;
        if (m_landedTime >= 300) {
            SetDead(true);
        }
    }
}

void Sun::OnClick() {
    if (!IsDead()) {
        m_world->AddSun(25);
        SetDead(true);
    }
}
