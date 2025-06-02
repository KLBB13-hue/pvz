#ifndef BACKGROUND_HPP__
#define BACKGROUND_HPP__

#include "pvz/GameObject/GameObject.hpp"

class Background : public GameObject {
public:
    Background(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
    ~Background() = default;

    void Update() override;
    void OnClick() override;
};

#endif // !BACKGROUND_HPP__
