#include "pvz/GameObject/Wallnut.hpp"

Wallnut::Wallnut(int x, int y, GameWorld* world)
    : Plant(ImageID::WALLNUT,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE) {
    // 坚果墙只需要显示
}
