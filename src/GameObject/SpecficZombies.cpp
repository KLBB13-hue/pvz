#include "pvz/GameObject/SpecificZombies.hpp"
#include "pvz/GameObject/Pea.hpp"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/utils.hpp"

// 普通僵尸实现
// 普通僵尸实现
NormalZombie::NormalZombie(int x, int y, GameWorld* world)
    : Zombie(ImageID::REGULAR_ZOMBIE, x, y, 20, 80, 200, world) {}

void NormalZombie::Update() {
    Zombie::Update();
    if (IsDead()) return;

    // 检测前方植物
    int gridX = GetX() - GetWidth()/2;
    int gridY = GetY();
    auto plant = m_world->GetPlantAt(gridX, gridY);

    // 获取当前动画ID
    AnimID currentAnim = GetState();

    // 状态处理
    if (plant) {
        // 如果当前不是EAT状态，则切换到EAT
        if (currentAnim != AnimID::EAT) {
            PlayAnimation(AnimID::EAT);
            SetState(AnimID::EAT);
        }
        AttackPlant(); // 每次检测到植物都攻击
    } else {
        // 如果当前不是WALK状态，则切换到WALK
        if (currentAnim != AnimID::WALK) {
            PlayAnimation(AnimID::WALK); // 只会在植物消失时调用一次
            SetState(AnimID::WALK); // 状态切换为行走
        }
        // 移动（无论是否改变状态）
        MoveTo(GetX() - 1, GetY());
    }
}

// 撑杆跳僵尸实现
PoleVaultingZombie::PoleVaultingZombie(int x, int y, GameWorld* world)
    : Zombie(ImageID::BUCKET_HEAD_ZOMBIE, x, y, 20, 80, 1300, world) {}

void PoleVaultingZombie::Update() {
    // 撑杆跳僵尸每帧向左移动2像素
    MoveTo(GetX() - 2, GetY());
}

// 铁桶僵尸实现
BucketHeadZombie::BucketHeadZombie(int x, int y, GameWorld* world)
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, x, y, 20, 80, 340, world) {}

void BucketHeadZombie::Update() {
    // 铁桶僵尸每帧向左移动1像素
    MoveTo(GetX() - 1, GetY());
}