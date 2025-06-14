#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>
#include <vector>

#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"
#include "pvz/GameObject/Grid.hpp"
#include "pvz/GameObject/ShovelButton.hpp"
#include "pvz/GameObject/Pea.hpp"

class ShovelButton;
class SeedButton;
class Grid;

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
    //textlist添加方法
    void AddText(std::shared_ptr<TextBase> text) {
        m_textObjects.push_back(text);
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


    std::shared_ptr<Grid> GetGridAt(int x, int y);
    std::shared_ptr<ShovelButton> GetShovelButton() const { return m_shovelButton; }
    bool IsShovelSelected() const { return m_shovelSelected; }
    void SetShovelSelected(bool selected) { m_shovelSelected = selected; }
    std::shared_ptr<Plant> GetPlantAt(int x, int y);
    bool HasZombieInLane(int plantX, int plantY) const;
    void HandleExplosion(int x, int y, int width, int height);
    void CheckPeaCollisions(int peaX, int peaY, int peaWidth, int peaHeight, Pea* pea);
    void CheckPeaCollisions(int peaX, int peaY, int peaWidth, int peaHeight, std::shared_ptr<Pea> pea);
private:
    std::list<std::shared_ptr<GameObject>> m_gameObjects;
    SeedButton* m_selectedSeed = nullptr;
    int m_sunCount = 50;
    int m_sunDropTimer;
    std::shared_ptr<TextBase> m_sunText;
    std::vector<std::shared_ptr<Grid>> m_grids;
    bool m_shovelSelected = false;
    std::shared_ptr<ShovelButton> m_shovelButton;
    int m_waveCount = 0;
    int m_nextWaveTimer = 1200;
    std::shared_ptr<TextBase> m_waveText;
    std::list<std::shared_ptr<TextBase>> m_textObjects;
};

#endif // !GAMEWORLD_HPP__