#include "pvz/GameObject/GameObject.hpp"

// Your everything begins from here.

GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : ObjectBase(imageID, x, y, layer, width, height, animID) {
    // Additional initialization if needed
}

