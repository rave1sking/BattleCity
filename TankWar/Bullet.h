#ifndef _BULLET_H_
#define _BULLET_H_

#include "Object.h"

class Bullet : public Object
{
public:
    Bullet();
    Bullet(Point pos, Dir dir);
    ~Bullet();
    void Display();
    void Move();
    bool IsDisapear()
    {
        return m_Disapear;
    }

protected:
    void CalculateSphere();
};

#endif
