#include "pvz/GameObject/Plant.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID) {
}
