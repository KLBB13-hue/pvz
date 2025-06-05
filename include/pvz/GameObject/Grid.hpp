#ifndef GRID_HPP__
#define GRID_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <memory>
#include "pvz/GameObject/Plant.hpp"

class GameWorld;

class Grid : public GameObject {
public:
    // 修改构造函数：层级改为 LAYER_UI
    Grid(int x, int y, GameWorld* world);
    virtual ~Grid() = default;

    void Update() override {}
    void OnClick() override;

    void ClearIfDead() {
        if (auto plant = m_plant.lock()) {
            if (plant->IsDead()) {
                m_plant.reset();
            }
        }
    }

    // 添加植物存在性检查
    bool HasPlant() const {
        return !m_plant.expired();
    }

    void SetPlant(std::shared_ptr<class Plant> plant) {
        if (plant) {
            m_plant = plant;
        } else {
            m_plant.reset();
        }
    }

    std::shared_ptr<class Plant> GetPlant() const {
        return m_plant.lock();
    }

private:
    GameWorld* m_world;
    std::weak_ptr<class Plant> m_plant;
};

#endif // !GRID_HPP__
