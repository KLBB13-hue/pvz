#include "pvz/GameObject/Repeater.hpp"

Repeater::Repeater(int x, int y, GameWorld* world)
    : Plant(ImageID::REPEATER,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,300) {
    // 双发射手只需要显示
}