#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "pvz/Framework/ObjectBase.hpp"


class GameWorld;

class GameObject : public ObjectBase
{
public:
    GameObject(ImageID imageID, int x, int y, LayerID layer,
               int width, int height, AnimID animID);
    virtual ~GameObject() = default;
    ImageID GetImageID() const { return ObjectBase::GetImageID(); }

    virtual bool CanBeClicked(int x, int y) const
    {
        return (std::abs(x - m_x) <= m_width / 2) &&
            (std::abs(y - m_y) <= m_height / 2);
    }

private:
    int m_x, m_y; // 对象中心位置
    int m_width, m_height; // 对象尺寸
};


#endif // !GAMEOBJECT_HPP__
