#ifndef WALLNUT_HPP__
#define WALLNUT_HPP__

#include "Plant.hpp"

class Wallnut : public Plant {
public:
    Wallnut(int x, int y, GameWorld* world);
    void Update() override;
    void OnClick() override;

private:
    bool m_isCracked;
};

#endif // !WALLNUT_HPP__
