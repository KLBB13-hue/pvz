#include "pvz/GameObject/ShovelButton.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

ShovelButton::ShovelButton(int x, int y, GameWorld* world)
    : GameObject(ImageID::SHOVEL,
                x, y,
                LayerID::UI,
                50, 50,
                AnimID::NO_ANIMATION),
      m_world(world)
{
    // 构造函数完成
}

void ShovelButton::Update() {
    // 铲子按钮不需要做任何更新操作
}

void ShovelButton::SetSelected(bool selected) {
    m_isSelected = selected;
    // 更新外观表示选中状态
    if (selected) {
        // 可以添加高亮效果
        // ChangeImage(ImageID::SHOVEL_SELECTED); // 如果有选中状态的图片
    } else {
        // ChangeImage(ImageID::SHOVEL); // 恢复默认状态
    }
}

void ShovelButton::OnClick() {
    // 清除任何已选中的种子
    if (m_world->IsSeedSelected()) {
        m_world->SetSelectedSeed(nullptr);
    }

    // 切换铲子状态
    bool newState = !m_isSelected;
    SetSelected(newState);
    m_world->SetShovelSelected(newState);
}