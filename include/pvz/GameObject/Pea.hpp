// Pea.hpp
#ifndef PEA_HPP__
#define PEA_HPP__

#include "pvz/GameObject/GameObject.hpp"

class GameWorld;

class Pea : public GameObject {
public:
    Pea(int x, int y, GameWorld* world);
    void Update() override;

private:
    GameWorld* m_world;
};

#endif // !PEA_HPP__
