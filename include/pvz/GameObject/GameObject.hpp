#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "pvz/Framework/ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase{
  // Use shared_from_this() instead of "this" to create a pointer to oneself.
public:
  GameObject(ImageID imageID, int x, int y, LayerID layer,
              int width, int height, AnimID animID);
  virtual ~GameObject() = default;




private:

};


#endif // !GAMEOBJECT_HPP__
