#ifndef COOLDOWNMASK_HPP__
#define COOLDOWNMASK_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp" // 确保包含常量定义

class SeedButton; // 前置声明

class CooldownMask : public GameObject {
public:
    CooldownMask(int x, int y);

    void Update() override;

    // 覆盖点击检测方法，使其永远返回false
    bool CanBeClicked(int x, int y) const override;

    // 覆盖点击处理方法，使其为空
    void OnClick() override {}

    // 设置关联的种子按钮
    void SetSeedButton(SeedButton* button) { m_seedButton = button; }

private:
    SeedButton* m_seedButton = nullptr; // 关联的种子按钮
};

#endif // !COOLDOWNMASK_HPP__