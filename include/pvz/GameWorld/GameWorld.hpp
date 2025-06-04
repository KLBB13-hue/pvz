#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/Grid.hpp"

class Peashooter;
class Sunflower;
class Wallnut;
class CherryBomb;
class Repeater;

class SeedButton; // 前置声明

class GameWorld : public WorldBase {
public:
    GameWorld() = default;
    ~GameWorld() = default;

    void Init() override;
    LevelStatus Update() override;
    void CleanUp() override;

    void AddObject(std::shared_ptr<GameObject> object) {
        m_gameObjects.push_back(object);
    }

    // 选中状态管理
    void SetSelectedSeed(SeedButton* seed) {
        m_selectedSeed = seed;
    }
    bool IsSeedSelected() const { return m_selectedSeed != nullptr; }
    SeedButton* GetSelectedSeed() const { return m_selectedSeed; }

    void AddPlant(int x, int y);

    void AddSun(int amount);

    int GetSunCount() const { return m_sunCount; }

    // 添加获取游戏对象的方法
    const std::list<std::shared_ptr<GameObject>>& GetObjects() const {
        return m_gameObjects;
    }

    std::shared_ptr<Grid> GetGridAt(int x, int y);

private:
    std::list<std::shared_ptr<GameObject>> m_gameObjects;
    SeedButton* m_selectedSeed = nullptr; // 当前选中的种子
    int m_sunCount = 50;
    int m_sunDropTimer;
    std::shared_ptr<TextBase> m_sunText;
    std::vector<std::shared_ptr<Grid>> m_grids;
};

#endif // !GAMEWORLD_HPP__
