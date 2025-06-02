// Grid.hpp
#ifndef GRID_HPP__
#define GRID_HPP__

#include "pvz/GameObject/GameObject.hpp"
#include <functional>

class Grid : public GameObject {
public:
    using ClickCallback = std::function<void(int, int)>;

    Grid(int x, int y, ClickCallback callback);
    virtual ~Grid() = default;

    void Update() override;
    void OnClick() override;

private:
    ClickCallback m_callback;
};

#endif // !GRID_HPP__
