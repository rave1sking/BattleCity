#include "EnemyTank.h"

void EnemyTank::RandomTank()
{
    //出现在屏幕上方:
    m_pos.SetX(rand() % Graphic::GetBattleGround().GetHeight());
    m_pos.SetY(28);
    m_dir = (Dir)(Dir::UP + (rand() % 4)); //随机确定坦克方向
    m_step = 2;

    m_stepCnt = rand() % MAX_STEP;
}

void EnemyTank::Display()
{
    IMAGE EnemyTank;
    switch (m_dir)
    {
    case UP:
        loadimage(&EnemyTank, L"..\\img\\enemytank\\enemyUP.gif",36,36);
        putimage(m_pos.GetX()-18, m_pos.GetY()-18, &EnemyTank);
        break;
    case DOWN:
        loadimage(&EnemyTank, L"..\\img\\enemytank\\enemyDOWN.gif", 36, 36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &EnemyTank);
        break;
    case RIGHT:
        loadimage(&EnemyTank, L"..\\img\\enemytank\\enemyRIGHT.gif", 36, 36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &EnemyTank);
        break;
    case LEFT:
        loadimage(&EnemyTank, L"..\\img\\enemytank\\enemyLEFT.gif", 36, 36);
        putimage(m_pos.GetX() - 18, m_pos.GetY() - 18, &EnemyTank);
        break;
    }
}

void EnemyTank::RandomDir(int type)
// 参数type为1时产生一个和当前方向不同的新方向，参数type为0时，产生任意一个新方向。
{
    if (type == 1)
    {
        Dir dir;
        while ((dir = (Dir)(Dir::UP + (rand() % 4))) == m_dir) {} 
        m_dir = dir;
    }
    else
    {
        m_dir = (Dir)(Dir::UP + (rand() % 4));
    }
}
void EnemyTank::Move()
{
    switch (m_dir)
    {
    case UP:
        m_pos.SetY(m_pos.GetY() - m_step); // -2 确保不会碰撞
        if (m_rectSphere.GetStartPoint().GetY()-2 < Graphic::GetBattleGround().GetStartPoint().GetY())
        {
            m_pos.SetY(m_pos.GetY() + m_step);
            this->RandomDir(1);
        }
        break;
    case DOWN:
        m_pos.SetY(m_pos.GetY() + m_step);
        if (m_rectSphere.GetEndPoint().GetY() +2 > Graphic::GetBattleGround().GetEndPoint().GetY())
        {
            m_pos.SetY(m_pos.GetY() - m_step);
            this->RandomDir(1);
        }
        break;
    case LEFT:
        m_pos.SetX(m_pos.GetX() - m_step);
        if (m_rectSphere.GetStartPoint().GetX() -2 < Graphic::GetBattleGround().GetStartPoint().GetX())
        {
            m_pos.SetX(m_pos.GetX() + m_step);  this->RandomDir(1);
        }
        break;
    case RIGHT:
        m_pos.SetX(m_pos.GetX() + m_step);
        if (m_rectSphere.GetEndPoint().GetX() +2 > Graphic::GetBattleGround().GetEndPoint().GetX())
        {
            m_pos.SetX(m_pos.GetX() - m_step); this->RandomDir(1);
        }
        break;
    default:
        break;
    }

    m_stepCnt++;
    if (m_stepCnt >= MAX_STEP)  //要写>=因为可能一上来就会 m_stepCnt = MAX_STEP
    {
        m_stepCnt = 0;
        this->RandomDir(0);
    }
    if (m_stepCnt % MAX_STEP_SHOOT == 0)  //每三步进行一次射击
    {
        m_NeedShoot = true;
    }
    CalculateSphere();

}

void EnemyTank::CalculateSphere()
{
    switch (m_dir)
    {
    case UP:
    case DOWN:
        m_rectSphere.Set(m_pos.GetX() - 18, m_pos.GetY() - 18, m_pos.GetX() + 18, m_pos.GetY() + 18);
        break;
    case LEFT:
    case RIGHT:
        m_rectSphere.Set(m_pos.GetX() - 18, m_pos.GetY() - 18, m_pos.GetX() + 18, m_pos.GetY() + 18);
        break;
    default:
        break;
    }
}

void EnemyTank::Shoot(list<Bullet*>& lstBullets)
{
    Bullet* eBullet = new Bullet(m_pos, m_dir);

    lstBullets.push_back(eBullet);

    m_NeedShoot = false;
}

bool EnemyTank::NeedShoot()
{
    return m_NeedShoot;
}