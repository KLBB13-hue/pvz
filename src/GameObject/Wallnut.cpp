#include "pvz/GameObject/Wallnut.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Wallnut::Wallnut(int x, int y, GameWorld* world)
    : Plant(ImageID::WALLNUT,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,4000),
      m_isCracked(false) {}

void Wallnut::Update() {
    Plant::Update();
    if (IsDead()) {
        return;
    }

    if (!m_isCracked && GetHP() < 4000 / 3) {
        ChangeImage(ImageID::WALLNUT_CRACKED);
        m_isCracked = true;
    }
}

void Wallnut::OnClick() {}