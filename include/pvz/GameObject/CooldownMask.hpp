#ifndef COOLDOWNMASK_HPP__
#define COOLDOWNMASK_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp" // 确保包含常量定义

class SeedButton; // 前置声明

class CooldownMask : public GameObject {
public:
    CooldownMask(int x, int y);

    void Update() override;


    bool CanBeClicked(int x, int y) const override;


    void OnClick() override {}


    void SetSeedButton(SeedButton* button) { m_seedButton = button; }

private:
    SeedButton* m_seedButton = nullptr; // 关联的种子按钮
};

#endif // !COOLDOWNMASK_HPP__