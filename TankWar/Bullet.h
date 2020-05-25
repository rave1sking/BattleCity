#ifndef _BULLET_H_
#define _BULLET_H_

#include "Bomb.h"
#include "Graphic.h"

class Bullet
{
public:
    Bullet();
    Bullet(Point pos, Dir dir);
    ~Bullet();
    void Display();
    void Move();
    bool IsDisappear()
    {
        return m_Disappear;
    }
    void bomb(list<Bomb*>& Bombs);
    Rect GetSphere()
    {
        return m_rectSphere;
    }
    void SetDisappear()
    {
        m_Disappear = true;
    }
    Point m_pos;
protected:
    void CalculateSphere();
    bool m_Disappear;
    int m_step;
    Dir m_dir;
    Rect m_rectSphere;
};

#endif
