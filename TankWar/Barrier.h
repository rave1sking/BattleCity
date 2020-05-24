#ifndef _BARRIER_H
#define _BARRIER_H

#include "Graphic.h"

class Barrier
{

protected:
    bool m_Disappear;
    Point m_pos;
    Rect m_rectSphere;
    int m_Type;

public:
    Barrier(Point pos, int Type);
    Barrier(int x,int y,int Type);
    ~Barrier() {};
    void Display();
    bool IsDisappear();
    void SetDisappear();
    Rect GetSphere();
    void CalculateSphere();
    int GetTpye();
    IMAGE barrier1;
    IMAGE barrier2;
    IMAGE barrier3;
    void InitBarrierImage();
};


#endif