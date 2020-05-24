#ifndef __MAIN_TANK__
#define __MAIN_TANK__

#include "Tank.h"
#include "Bullet.h"

class MainTank : public Tank
{
public:
    MainTank():Tank()
    {
        m_pos.Set(300, 700);
        this->CalculateSphere();
        m_dir = Dir::UP;
        m_step = 6;

    }

    ~MainTank() {}

    // 设置行驶方向
    void SetDir(Dir dir);
    void Display();
    void Move();
    void Shoot(list<Bullet*>& Bullets);
    Rect GetSphere()
    {
        return m_rectSphere;
    }
    IMAGE maintankUP;
    IMAGE maintankDOWN;
    IMAGE maintankLEFT;
    IMAGE maintankRIGHT;
    void InitMainTankImage();
protected:
    //坦克所占矩形体积
    void CalculateSphere();
    // 绘制坦克主体
    void DrawTankBody();
};

#endif