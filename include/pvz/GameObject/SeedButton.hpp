#ifndef SEEDBUTTON_HPP__
#define SEEDBUTTON_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class GameWorld;

class SeedButton : public GameObject {
public:
    SeedButton(ImageID imageID, int x, int y, int price, GameWorld* world);
    virtual ~SeedButton() = default;

    void Update() override {}
    void OnClick() override;

    int GetPrice() const { return m_price; }
    ImageID GetPlantImageID() const { return m_plantImageID; }

    // 添加状态检查方法
    bool IsSelected() const { return m_isSelected; }
    void SetSelected(bool selected);
private:
    GameWorld* m_world;
    int m_price;
    ImageID m_plantImageID;
    bool m_isSelected = false;
};

#endif // !SEEDBUTTON_HPP__