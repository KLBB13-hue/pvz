// Sunflower.hpp
#ifndef SUNFLOWER_HPP__
#define SUNFLOWER_HPP__

#include "Plant.hpp"

class Sunflower : public Plant {
public:
    Sunflower(int x, int y);
    virtual ~Sunflower() = default;

    void Update() override;
    void OnClick() override;
};

#endif // !SUNFLOWER_HPP__