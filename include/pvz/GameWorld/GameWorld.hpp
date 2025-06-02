#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"

#include "pvz/GameObject/GameObject.hpp"

#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"

class GameWorld : public WorldBase {
public:
  // Consider:
  // Use shared_from_this() instead of "this" to create a pointer to oneself?
  // Use unique_ptr<> / shared_ptr<> to manage GameObjects?
  GameWorld() = default;
  ~GameWorld() = default;

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

private:
  std::list<std::shared_ptr<GameObject>> m_gameObjects;

public:
  void AddObject(std::shared_ptr<GameObject> object) {
    m_gameObjects.push_back(object);
  }
  void AddPlant(int x, int y);

};

#endif // !GAMEWORLD_HPP__
