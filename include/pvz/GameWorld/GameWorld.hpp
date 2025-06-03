#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"

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
        m_shovelSelected = false;
    }
    void SetShovelSelected(bool selected) {
        m_shovelSelected = selected;
        m_selectedSeed = nullptr;
    }
    bool IsSeedSelected() const { return m_selectedSeed != nullptr; }
    bool IsShovelSelected() const { return m_shovelSelected; }
    SeedButton* GetSelectedSeed() const { return m_selectedSeed; }

    void AddPlant(int x, int y);

    void AddSun(int amount);

    int GetSunCount() const { return m_sunCount; }

private:
    std::list<std::shared_ptr<GameObject>> m_gameObjects;
    SeedButton* m_selectedSeed = nullptr; // 当前选中的种子
    bool m_shovelSelected = false;
    int m_sunCount = 50; // 铲子是否被选中
    int m_sunDropTimer;
    std::shared_ptr<TextBase> m_sunText;
};

#endif // !GAMEWORLD_HPP__
