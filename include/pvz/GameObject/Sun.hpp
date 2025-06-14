#pragma once
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

class GameWorld;
class Sun : public GameObject {
public:
    enum SunType { FALLING_SUN, SUNFLOWER_SUN };

    Sun(int x, int y, SunType type, GameWorld* world);
    void Update() override;
    void OnClick() override;

private:
    SunType m_type;
    int m_state;          // 0=未落地, 1=已落地
    int m_countdown;      // 落地倒计时
    int m_vy;             // 向日葵阳光的垂直速度
    int m_landedTime;     // 落地后经过的tick
    GameWorld* m_world;
};