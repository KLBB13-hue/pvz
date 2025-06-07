#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameObject/ShovelButton.hpp"

class ShovelButton;
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

    void RemovePlant(int x, int y);


    void GenerateWave();

    // 添加获取游戏对象的方法
    const std::list<std::shared_ptr<GameObject>>& GetObjects() const {
        return m_gameObjects;
    }

    std::shared_ptr<Grid> GetGridAt(int x, int y);
    std::shared_ptr<ShovelButton> GetShovelButton() const { return m_shovelButton; }


    bool IsShovelSelected() const { return m_shovelSelected; }
    void SetShovelSelected(bool selected) { m_shovelSelected = selected; }
    std::shared_ptr<Plant> GetPlantAt(int x, int y);
private:
    std::list<std::shared_ptr<GameObject>> m_gameObjects;
    SeedButton* m_selectedSeed = nullptr; // 当前选中的种子
    int m_sunCount = 50;
    int m_sunDropTimer;
    std::shared_ptr<TextBase> m_sunText;
    std::vector<std::shared_ptr<Grid>> m_grids;
    bool m_shovelSelected = false; // 铲子选中状态
    std::shared_ptr<ShovelButton> m_shovelButton; // 铲子按钮对象
    int m_waveCount = 0; // 初始为第0波
    int m_nextWaveTimer = 1200;
    std::shared_ptr<TextBase> m_waveText;


};

#endif // !GAMEWORLD_HPP__