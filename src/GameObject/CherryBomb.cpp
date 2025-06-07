#include "pvz/GameObject/CherryBomb.hpp"

CherryBomb::CherryBomb(int x, int y, GameWorld* world)
    : Plant(ImageID::CHERRY_BOMB,
            x, y,
            LayerID::PLANTS,
            LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT,
            AnimID::IDLE,4000) {
    // 樱桃炸弹只需要显示
}