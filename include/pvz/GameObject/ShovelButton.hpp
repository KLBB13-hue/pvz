#ifndef SHOVELBUTTON_HPP__
#define SHOVELBUTTON_HPP__

#include "pvz/GameObject/GameObject.hpp"

class GameWorld;

class ShovelButton : public GameObject {
public:
    ShovelButton(int x, int y, GameWorld* world);
    virtual ~ShovelButton() = default;

    void Update() override {}
    void OnClick() override;

private:
    GameWorld* m_world;
};

#endif // !SHOVELBUTTON_HPP__
