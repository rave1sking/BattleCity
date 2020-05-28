#pragma once
#ifndef __ENEMY_TANK__
#define __ENEMY_TANK__

#define MAX_STEP 10
#include "Tank.h"
#include "Bullet.h"
class EnemyTank : public Tank
{
public:
    EnemyTank()
    {
        RandomTank();
    }

    ~EnemyTank() {}

    void Display();
    void Move();
    Rect GetSphere()
    {
        return m_rectSphere;
    }
    void Shoot(list<Bullet*>& eBullets);
    bool NeedShoot();
    void SetPos(Point pos);
    void RandomDir(int type);
    EnemyTank& operator=(const EnemyTank& obj)
    {
        m_dir = obj.m_dir;
        m_pos = obj.m_pos;
        m_step = obj.m_step;
        m_rectSphere = obj.m_rectSphere;
    }
protected:
    void CalculateSphere();
    void RandomTank();
    // 随机产生坦克方向 type： 1, 新方向必须与之前方向不同 else 任意一个新方向
    int m_stepCnt;//来记录坦克当前行驶的步数
    bool m_NeedShoot = false;
    int MAX_STEP_SHOOT = 20;
};

#endif