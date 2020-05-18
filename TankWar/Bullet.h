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
protected:
    void CalculateSphere();
    bool m_Disappear;
    Point m_pos;
    int m_step;
    Dir m_dir;
    Rect m_rectSphere;
};

#endif
