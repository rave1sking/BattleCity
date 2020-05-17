#ifndef __TANK_H__
#define __TANK_H__

#include "Object.h"

#include <list>

using namespace std;

class Tank : public Object
{
public:
    Tank()
    {
        m_pos.Set(300, 300);
        //this->CalculateSphere();
        m_dir = Dir::UP;
        m_step = 4;
        m_Disapear = false;
    }
    ~Tank() {}
    //void Display();
    //void Move();
    void Shoot(list<Object*>& Bullets);

    bool IsDisapear()
    {
        return m_Disapear;
    }
protected:
    void CalculateSphere();
};

#endif