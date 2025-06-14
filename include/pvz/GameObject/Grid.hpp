#ifndef GRID_HPP__
#define GRID_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <memory>
#include "pvz/GameObject/Plant.hpp"

class GameWorld;

class Grid : public GameObject {
public:
    Grid(int x, int y, GameWorld* world);
    virtual ~Grid() = default;

    void Update() override {}
    void OnClick() override;

    void SetPlant(std::shared_ptr<class Plant> plant) {
        m_plant = plant;
    }

    std::shared_ptr<class Plant> GetPlant() const {
        return m_plant.lock();
    }

    void ClearIfDead() {
        if (auto plant = m_plant.lock()) {
            if (plant->IsDead()) {
                m_plant.reset();
            }
        }
    }

    bool HasPlant() const {
        return !m_plant.expired();
    }

private:
    GameWorld* m_world;
    std::weak_ptr<class Plant> m_plant;
};

#endif // !GRID_HPP__

