#include "pvz/GameObject/Wallnut.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Wallnut::Wallnut(int x, int y, GameWorld* world)
    : Plant(ImageID::WALLNUT,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,4000),
      m_isCracked(false) { // 初始未受损
    // 坚果墙只需要显示
}

void Wallnut::Update() {
    // 先调用基类的Update
    Plant::Update();

    // 如果已经死亡，则直接返回
    if (IsDead()) {
        return;
    }

    // 检查是否需要更换为受损贴图
    if (!m_isCracked && GetHP() < 4000 / 3) {
        ChangeImage(ImageID::WALLNUT_CRACKED);
        m_isCracked = true;
    }
}

void Wallnut::OnClick() {

}
