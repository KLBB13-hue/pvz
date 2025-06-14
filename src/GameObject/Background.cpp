#include "pvz/GameObject/Background.hpp"

Background::Background(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID) {}

void Background::Update() {}

void Background::OnClick() {}