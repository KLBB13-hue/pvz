#ifndef GRID_HPP__
#define GRID_HPP__

#include "pvz/GameObject/GameObject.hpp"

// 前置声明 GameWorld
class GameWorld;

class Grid : public GameObject {
public:
    // 构造函数改为接收 GameWorld 指针
    Grid(int x, int y, GameWorld* world);
    virtual ~Grid() = default;

    void Update() override;
    void OnClick() override;

    // 新增方法：设置/获取当前网格上的植物
    void SetPlant(std::shared_ptr<class Plant> plant) { m_plant = plant; }
    std::shared_ptr<class Plant> GetPlant() const { return m_plant.lock(); }

private:
    GameWorld* m_world; // 直接持有 GameWorld 指针
    std::weak_ptr<class Plant> m_plant; // 新增：当前网格上的植物
};

#endif // !GRID_HPP__
