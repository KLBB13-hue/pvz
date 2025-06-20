#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "pvz/GameObject/GameObject.hpp"

class Plant : public GameObject {
public:
    Plant(ImageID imageID, int x, int y, LayerID layer,
          int width, int height, AnimID animID, int hp);
    virtual ~Plant() = default;

    int GetHP() const;
    void TakeDamage(int damage);
    virtual void Update() override;

    virtual void OnClick() override;
    virtual bool CanBeShoveled() const { return true; }

    void SetWorld(GameWorld* world);
    GameWorld* GetWorld() const;

    bool ContainsPoint(int x, int y) const;

private:
    GameWorld* m_world = nullptr;
    int m_hp;
};

#endif // !PLANT_HPP__