#include "pvz/GameObject/ShovelButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

ShovelButton::ShovelButton(int x, int y, GameWorld* world)
    : GameObject(ImageID::SHOVEL,
                x, y,
                LayerID::UI,
                50, 50,
                AnimID::NO_ANIMATION),
      m_world(world) {}

void ShovelButton::Update() {}

void ShovelButton::SetSelected(bool selected) {
    m_isSelected = selected;
}

void ShovelButton::OnClick() {
    if (m_world->IsSeedSelected()) {
        m_world->SetSelectedSeed(nullptr);
    }

    bool newState = !m_isSelected;
    SetSelected(newState);
    m_world->SetShovelSelected(newState);
}