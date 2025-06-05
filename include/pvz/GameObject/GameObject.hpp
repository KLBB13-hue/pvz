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
    ImageID GetImageID() const { return ObjectBase::GetImageID(); }
    // 添加新方法
    virtual bool CanBeClicked(int x, int y) const {
        // 默认实现：矩形检测
        return (std::abs(x - m_x) <= m_width / 2) &&
               (std::abs(y - m_y) <= m_height / 2);
    }


private:
    int m_x, m_y;         // 对象中心位置
    int m_width, m_height; // 对象尺寸

};


#endif // !GAMEOBJECT_HPP__
