#include "pvz/GameObject/Background.hpp"

Background::Background(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID) {
}

void Background::Update() {
    // Background doesn't need per-frame updates
}

void Background::OnClick() {
    // Background click handler - can be left empty or add debug output
}