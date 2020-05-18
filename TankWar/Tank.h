#ifndef __TANK_H__
#define __TANK_H__

#include "Graphic.h"
#include <list>

using namespace std;
class Tank
{
public:
    Tank()
    {
        m_pos.Set(300, 300);
        m_dir = Dir::UP;
       // this->CalculateSphere();
        m_step = 4;
        m_Disappear = false; 
    }
    ~Tank() {}
    void Display();
    void Move();
    bool IsDisappear()
    {
        return m_Disappear;
    }
    Rect GetSphere()
    {
        return m_rectSphere;
    }
    void SetDisappear()
    {
        m_Disappear = true;
    }
protected:
    void CalculateSphere();
    bool m_Disappear;
    int m_step;
    Point m_pos;
    Dir m_dir;
    Rect m_rectSphere; //∂‘œÛ∑∂Œß

};

#endif