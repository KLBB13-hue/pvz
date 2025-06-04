#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "pvz/GameObject/GameObject.hpp"

class Plant : public GameObject {
public:
    Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
    virtual ~Plant() = default;

    // 添加虚函数声明
    virtual void Update() override;
    virtual void OnClick() override;

    virtual bool CanBeShoveled() const { return true; } // 新增
    void SetWorld(GameWorld* world);
    GameWorld* GetWorld() const;
private:
    GameWorld* m_world = nullptr;

};

#endif // !PLANT_HPP__
