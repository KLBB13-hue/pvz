#include "pvz/GameObject/SpecificZombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
NormalZombie::NormalZombie(int x, int y, GameWorld* world)
    : Zombie(ImageID::REGULAR_ZOMBIE, x, y, 20, 80, 200, world)
{
    m_type = ZombieType::NORMAL;
}

void NormalZombie::PerformAction() {
    //僵尸所在网格
    int gridX = GetX() - GetWidth() / 2;
    int gridY = GetY();
    auto plant = m_world->GetPlantAt(gridX, gridY);

    AnimID currentAnim = GetState();

    if (plant) { //若有植物，且当前的动画不是EAT，则设置动画为EAT，防止反复更新使的动画停在第一帧
        if (currentAnim != AnimID::EAT) {
            SetState(AnimID::EAT);
        }
        AttackPlant();
    } else {
        if (currentAnim != AnimID::WALK) {
            SetState(AnimID::WALK);
        }
        Move();
    }
}