#include "pvz/GameObject/Peashooter.hpp"

Peashooter::Peashooter(int x, int y, GameWorld* world)
    : Plant(ImageID::PEASHOOTER,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE) {
    // 豌豆射手只需要显示，不需要特殊逻辑
}
