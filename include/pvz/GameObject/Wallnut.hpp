#ifndef WALLNUT_HPP__
#define WALLNUT_HPP__

#include "Plant.hpp"

class Wallnut : public Plant {
public:
    Wallnut(int x, int y, GameWorld* world);
    void Update() override;  // 重写Update方法
    void OnClick() override; // 重写点击处理方法

private:
    bool m_isCracked; // 标记是否已更换为受损贴图
};

#endif // !WALLNUT_HPP__
