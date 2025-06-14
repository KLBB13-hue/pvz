// CherryBomb.hpp
#ifndef CHERRY_BOMB_HPP__
#define CHERRY_BOMB_HPP__

#include "Plant.hpp"

class CherryBomb : public Plant {
public:
    CherryBomb(int x, int y, GameWorld* world);
    void Update() override;

private:
    GameWorld* m_world;
    int m_countdown = 15;
};

#endif // !CHERRY_BOMB_HPP__
