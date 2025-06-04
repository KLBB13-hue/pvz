#ifndef SHOVELBUTTON_HPP__
#define SHOVELBUTTON_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

class ShovelButton : public GameObject {
public:
    ShovelButton(int x, int y, GameWorld* world);
    void Update() override;
    void OnClick() override;

    bool IsSelected() const { return m_isSelected; }
    void SetSelected(bool selected);

private:
    GameWorld* m_world;
    bool m_isSelected = false;
};

#endif // !SHOVELBUTTON_HPP__
