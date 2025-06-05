#ifndef SEEDBUTTON_HPP__
#define SEEDBUTTON_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"
#include  "pvz/GameObject/CooldownMask.hpp"

class GameWorld;

class SeedButton : public GameObject {
public:
    SeedButton(ImageID imageID, int x, int y, int price, int cooldown, GameWorld* world);
    virtual ~SeedButton() = default;

    void Update() override;
    void OnClick() override;

    int GetPrice() const { return m_price; }
    ImageID GetPlantImageID() const { return m_plantImageID; }

    // 冷却相关方法
    void StartCooldown();
    bool IsCooling() const { return m_cooldownTimer > 0; }
    int GetCooldownTime() const { return m_cooldown; }
    int GetRemainingCooldown() const { return m_cooldownTimer; }

private:
    GameWorld* m_world;
    int m_price;
    int m_cooldown; // 冷却时间（帧数）
    int m_cooldownTimer = 0; // 冷却计时器
    ImageID m_plantImageID;
    std::shared_ptr<CooldownMask> m_cooldownMask; // 冷却遮盖物
};

#endif // !SEEDBUTTON_HPP__