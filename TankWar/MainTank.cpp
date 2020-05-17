#include "MainTank.h"
#include "Bullet.cpp"



void MainTank::SetDir(Dir dir)
{
    m_dir = dir;
}

void MainTank::DrawTankBody()
{
    IMAGE maintank;
    switch(m_dir)
    {
    case UP:
        loadimage(&maintank, L"..\\img\\mainup.gif",36,36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &maintank);
        break;
    case DOWN:
        loadimage(&maintank, L"..\\img\\maindown.gif",36,36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &maintank);
        break;
    case LEFT:
        loadimage(&maintank, L"..\\img\\mainleft.gif", 36, 36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &maintank);
        break;
    case RIGHT:
        loadimage(&maintank, L"..\\img\\mainright.gif", 36, 36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &maintank);
        break;
    }
}

void MainTank::Display()
{
    DrawTankBody();
}

void MainTank::Move()
{
    switch (m_dir)
    {
    case UP:
        m_pos.SetY(m_pos.GetY() - m_step);
        if (m_rectSphere.GetStartPoint().GetY() < Graphic::GetBattleGround().GetStartPoint().GetY())
            m_pos.SetY(m_pos.GetY() + m_step);
        break;
    case DOWN:
        m_pos.SetY(m_pos.GetY() + m_step);
        if (m_rectSphere.GetEndPoint().GetY() > Graphic::GetBattleGround().GetEndPoint().GetY())
            m_pos.SetY(m_pos.GetY() - m_step);
        break;
    case LEFT:
        m_pos.SetX(m_pos.GetX() - m_step);
        if (m_rectSphere.GetStartPoint().GetX() < Graphic::GetBattleGround().GetStartPoint().GetX())
            m_pos.SetX(m_pos.GetX() + m_step);
        break;
    case RIGHT:
        m_pos.SetX(m_pos.GetX() + m_step);
        if (m_rectSphere.GetEndPoint().GetX() > Graphic::GetBattleGround().GetEndPoint().GetX())
            m_pos.SetX(m_pos.GetX() - m_step);
        break;
    default:
        break;
    }

    CalculateSphere();
}

void MainTank::CalculateSphere() //:CalculateSphere
{
    switch (m_dir)
    {
    case UP:
    case DOWN:
        m_rectSphere.Set(m_pos.GetX()-18,m_pos.GetY()-18, m_pos.GetX()+18, m_pos.GetY()+18);
        break;
    case LEFT:
    case RIGHT:
        m_rectSphere.Set(m_pos.GetX() - 18, m_pos.GetY() - 18, m_pos.GetX() + 18, m_pos.GetY() + 18);
        break;
    default:
        break;
    } 
}

//新加设计功能
void MainTank::Shoot(list<Object*>& Bullets)
{
    Bullet* pBullet = new Bullet(m_pos,m_dir);
    Bullets.push_back(pBullet);
}