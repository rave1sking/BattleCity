#ifndef __BOMB_H__
#define __BOMB_H__
#include "Graphic.h"
#include <list>

using namespace std;

enum BombType
{
    L, //大号爆炸，用于摧毁坦克
    M, //中号爆炸，用于摧毁墙壁
    S  //小号爆炸，用于打出界面
}; 

class Bomb
{
public:
    Bomb();
    Bomb(Point pos, BombType type);
    ~Bomb() {}

    void Display();

    void Move();

    void Boom (list <Bomb*> & Bombs);

    bool IsDisappear();

protected:
    void CalculateSphere();
    IMAGE bomb;
    BombType m_type;
    bool m_Disappear;
    Dir m_dir;
    Point m_pos;

};

#endif
