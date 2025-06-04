#include "pvz/GameObject/Sun.hpp"
#include "pvz/utils.hpp"

Sun::Sun(int x, int y, SunType type, GameWorld* world)
    : GameObject(ImageID::SUN, x, y, LayerID::SUN , 80, 80, AnimID::IDLE)
    , m_type(type)
    , m_state(0)
    , m_countdown(0)
    , m_vy(0)
    , m_landedTime(0)
    , m_world(world) {

    if (type == FALLING_SUN) {
        // 随机掉落时间 [63, 263]
        m_countdown = randInt(63, 263);
    } else { // SUNFLOWER_SUN
        m_countdown = 12; // 固定12tick
        m_vy = -4; // 初始向上速度（y轴向下为正，所以负值表示向上）
    }
}

void Sun::Update() {
    if (m_state == 0) { // 未落地状态
        if (m_type == FALLING_SUN) {
            // 向下移动（屏幕坐标系y向下为正）
            MoveTo(GetX(), GetY() - 2);
        } else { // SUNFLOWER_SUN

            MoveTo(GetX() +2 , GetY() - m_vy );
            m_vy += 1; // 加速度向下
        }

        if (--m_countdown <= 0) {
            m_state = 1; // 标记为已落地
            m_landedTime = 0;
        }
    } else { // 已落地状态
        if (++m_landedTime >= 300) {
            SetDead(true); // 10秒后消失
        }
    }
}

void Sun::OnClick() {
    if (!IsDead()) {
        // 通知GameWorld增加阳光
        m_world->AddSun(25);
        SetDead(true);
    }
}
