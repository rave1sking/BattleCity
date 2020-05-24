#pragma warning(disable:4996)

#include <iostream>
#include <conio.h>
#include <time.h>
#include <list>
#include <stdlib.h>
#include <map>

#include "Graphic.h"
#include "MainTank.h"
#include "EnemyTank.h"
#include "EnemyTank.cpp"
#include "Bullet.cpp"
#include "Bomb.h"
#include "Bomb.cpp"
#include "Utils/Shape.cpp"
#include "Setting.h"
#include "Barrier.h"

#define MAX_ENEMYTANKS 5
#define MAX_BARRIERS 40 


using namespace std;
IMAGE img;
IMAGE base;


list<EnemyTank*> lstTanks;
list<Bullet*> MainBullets;
list<Bullet*> EnemyBullets;
list<Barrier*> Barrieies;
MainTank mainTank;
//检测坦克子弹和敌方坦克的碰撞
void Barrier::InitBarrierImage()
{
	loadimage(&barrier1, L"..\\img\\barrier\\normal.gif",30,30);
	loadimage(&barrier2, L"..\\img\\barrier\\steel.gif",30,30);
	loadimage(&barrier3, L"..\\img\\barrier\\grass.gif",30,30);
}
void CheckCrashMain_to_Enemy()
{
	for (list<Bullet*>::iterator it = MainBullets.begin(); it != MainBullets.end(); it++)
	{
		for (list<EnemyTank*>::iterator itt = lstTanks.begin(); itt != lstTanks.end(); itt++)
		{
			Rect a = (*it)->GetSphere(); 
			Rect b = (*itt)->GetSphere();
			if (Shape::CheckIntersect(a, b))
			{
				(*itt)->SetDisappear();
				(*it)->SetDisappear();
			}
		}
	}
}

void CheckCrashEnemy_to_Main()
{
	for (list<Bullet*>::iterator it = EnemyBullets.begin(); it != EnemyBullets.end(); it++)
	{
			Rect a = (*it)->GetSphere();
			Rect b = mainTank.GetSphere();
			if (Shape::CheckIntersect(a, b))
			{
				Setting::Die();
				if (Setting::GetLife() > 0)
				{
					(*it)->SetDisappear();
				}
				else
				{
					mainTank.SetDisappear();
				}
			}
		}
}

//检测坦克之间是否碰撞
void CheckCrashEnemyTank()
{
	for (list<EnemyTank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
		for (list<EnemyTank*>::iterator itt = lstTanks.begin(); itt != lstTanks.end(); itt++)
		{
			if (*itt== *it)  //自己和自己不检测
				continue;
			else
			{
				Rect a = (*it)->GetSphere();
				Rect b = (*itt)->GetSphere();
				if (Shape::CheckIntersect(a, b))
				{
					Dir dir;
					while ((dir = (Dir)(Dir::UP + (rand() % 4))) == (*it)->m_dir) {}
					(*it)->m_dir = dir;
				}
			}
		}
}


void CheckCrashBullets_to_Barriers()
{

	for (list<Bullet*>::iterator it1 = EnemyBullets.begin(); it1 != EnemyBullets.end(); it1++)
		for (list<Barrier*>::iterator it2 = Barrieies.begin(); it2 != Barrieies.end(); it2++)
			if ((*it2)->GetTpye() == 1)
			{
				Rect a = (*it1)->GetSphere();
				Rect b = (*it2)->GetSphere();
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->SetDisappear();
					(*it2)->SetDisappear();           //如果碰到Normal，子弹和墙都消失
				}
			}
			else
				if ( ((*it2)->GetTpye()) == 2)
				{
					Rect a = (*it1)->GetSphere();
					Rect b = (*it2)->GetSphere();
					if (Shape::CheckIntersect(a, b))
					{
						(*it1)->SetDisappear();        //如果碰到steel,子弹消失
					}
				}
	for (list<Bullet*>::iterator it1 = MainBullets.begin(); it1 != MainBullets.end(); it1++)
		for (list<Barrier*>::iterator it2 = Barrieies.begin(); it2 != Barrieies.end(); it2++)
			if ((*it2)->GetTpye() == 1)
			{
				Rect a = (*it1)->GetSphere();
				Rect b = (*it2)->GetSphere();
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->SetDisappear();
					(*it2)->SetDisappear();           //如果碰到Normal，子弹和墙都消失
				}
			}
			else
				if ((*it2)->GetTpye() == 2)
				{
					Rect a = (*it1)->GetSphere();
					Rect b = (*it2)->GetSphere();
					if (Shape::CheckIntersect(a, b))
					{
						(*it1)->SetDisappear();        //如果碰到steel,子弹消失
					}
				}
	       //如果碰到water,子弹穿过
}

//检测坦克和墙壁的碰撞


void CheckCrashTank_to_Barriers()
{
	for (list<EnemyTank*>::iterator it1 = lstTanks.begin(); it1 != lstTanks.end(); it1++)
		for (list<Barrier*>::iterator it2 = Barrieies.begin(); it2 != Barrieies.end(); it2++)
		{
			Rect a = (*it1)->GetSphere();
			Rect b = (*it2)->GetSphere();
			//EnemyTank virtual_Enemytank;
			//virtual_Enemytank = (*it1) ;
			switch ((*it1)->m_dir)
			{
			case UP:
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->m_pos.SetY((*it1)->m_pos.GetY() + 2);
					(*it1)->RandomDir(1);
				}
				break;
			case DOWN:
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->m_pos.SetY((*it1)->m_pos.GetY() - 2);
					(*it1)->RandomDir(1);
				}
				break;
			case LEFT:
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->m_pos.SetX((*it1)->m_pos.GetX() + 2);
					(*it1)->RandomDir(1);
				}
				break;
			case RIGHT:
				if (Shape::CheckIntersect(a, b))
				{
					(*it1)->m_pos.SetX((*it1)->m_pos.GetX() - 2);
					(*it1)->RandomDir(1);
				}
				break;
			default:
				break;
			}
		}
	for (list<Barrier*>::iterator it = Barrieies.begin(); it != Barrieies.end(); it++)
	{
		Rect b = mainTank.GetSphere();
		Rect a = (*it)->GetSphere();

		MainTank virtual_a;
		virtual_a = mainTank;
		switch (mainTank.m_dir)
		{
		case UP:
			virtual_a.m_pos.SetY((mainTank.m_pos.GetY() - 18));
			if (Shape::CheckIntersect(a, b) && Shape::CheckPointInRect(virtual_a.m_pos,a))
			{
				  mainTank.m_pos.SetY(mainTank.m_pos.GetY() + 6);
			}
			break;
		case DOWN:
			virtual_a.m_pos.SetY((mainTank.m_pos.GetY() + 18));
			if (Shape::CheckIntersect(a, b) && Shape::CheckPointInRect(virtual_a.m_pos, a))
			{
				 mainTank.m_pos.SetY(mainTank.m_pos.GetY() - 6);
			}
			break;
		case LEFT:
			virtual_a.m_pos.SetX((mainTank.m_pos.GetX() - 18));
			if (Shape::CheckIntersect(a, b) && Shape::CheckPointInRect(virtual_a.m_pos, a))
			{
				 mainTank.m_pos.SetX(mainTank.m_pos.GetX() + 6);
			}
			break;
		case RIGHT:
			virtual_a.m_pos.SetX((mainTank.m_pos.GetX() + 18));
			if (Shape::CheckIntersect(a, b) && Shape::CheckPointInRect(virtual_a.m_pos, a))
			{
				mainTank.m_pos.SetX(mainTank.m_pos.GetX() - 6);
			}
			break;
		default:
			break;

		}
	}
}



//生成地图
void CreateMap()
{
	//创建Point list，向list中添加Point，
	loadimage(&base, L"..\\img\\base.png",90,90);
	list<Point> POINT1;
	Point x1[100]; 
	int i = 0;
	for (int x = 30; x <= 780; x += 30,i++)
	{
		x1[i].SetX(x);
		x1[i].SetY(400);
		POINT1.push_back(x1[i]);
	}
	//搭建基地四周的墙
	list<Point> POINT2;
	Point x2[100];
	int j = 0;
	for (int y = 653; y <= 743; y += 30,j++)
	{
		x2[j].SetX(335);
		x2[j].SetY(y);
		POINT2.push_back(x2[j]);
	}
	for (int x = 335; x <= 455; x += 30, i++)
	{
		x2[i].SetX(x);
		x2[i].SetY(653);
		POINT2.push_back(x2[i]);
	}
	for (int y = 683; y <= 743; y += 30, i++)
	{
		x2[i].SetX(455);
		x2[i].SetY(y);
		POINT2.push_back(x2[i]);
	}
	list<Point>::iterator B;
	for (B = POINT1.begin(); B != POINT1.end(); B++)
	{
		Barrier* b = new Barrier(*B,1);
		b->InitBarrierImage();
		Barrieies.push_back(b);
	} 
	for (B = POINT2
		.begin(); B != POINT2.end(); B++)
	{
		Barrier* b = new Barrier(*B, 2);
		b->InitBarrierImage();
		Barrieies.push_back(b);
	}
	/*
	Point a(500, 500);
	Barrier *b = new Barrier(a, 1);
	b->InitBarrierImage();
	Barrieies.push_back(b); 
	*/
}







int main()
{
	Graphic::Create();
	//BeginBatchDraw();
	//按F进入坦克
	/*
	IMAGE img2;
	loadimage(&img2, L"..\\img\\startimg.png",1024,768);
	putimage(0,0, &img2);
	char m;
	m = getchar();
	while (m != 'f' && m != 'F')
		m = getchar();
	*/
	lstTanks.clear();
	//子弹的实现：
    //主坦克子弹
	MainBullets.clear();
    //敌人坦克子弹
	EnemyBullets.clear();
    //墙的实现
	Barrieies.clear();

	bool bGameOver = false;
	bool loop = true;
	bool skip = false;
	initEnemyTankimage();
	mainTank.InitMainTankImage();
	InitBulletsimage();
	CreateMap();
	while (loop)
	{
		if (Setting::m_bNewLevel)
		{
			Sleep(1000);

			Setting::m_bNewLevel = false;

			Setting::NewGameLevel();

			for (int i = 0; i < Setting::GetTankNum(); i++)
			{
				EnemyTank* p = new EnemyTank();
				lstTanks.push_back(p);
			}
		}
		if (kbhit())
		{
			int key = getch();
			switch (key)
			{
				// Up
			case 72:
				mainTank.SetDir(Dir::UP);
				break;
				// Down
			case 80:
				mainTank.SetDir(Dir::DOWN);
				break;
				// Left
			case 75:
				mainTank.SetDir(Dir::LEFT);
				break;
				// Right
			case 77:
				mainTank.SetDir(Dir::RIGHT);
				break;
			case 224: // 方向键高8位
				break;
				// Esc 退出
			case 27:
				loop = false;
				break;
				// 32是空格Space 计划发射子弹
			case 32:
				mainTank.Shoot(MainBullets);
				break;
				// 13是Enter Enter暂停
			case 13:
				if (skip)
					skip = false;
				else
					skip = true;
				break;
			default:
				break;
			}
		}

		if (!skip)
		{
			cleardevice();
			BeginBatchDraw();
			putimage(350, 668, &base);
			CheckCrashMain_to_Enemy();
			CheckCrashEnemy_to_Main();
			CheckCrashEnemyTank();
			CheckCrashBullets_to_Barriers();
			CheckCrashTank_to_Barriers();
			Graphic::DrawBattleGround();

			if (Setting::m_bNewLevel)
			{
				Setting::m_bNewLevel = false;

				Setting::NewGameLevel();

				//Graphic::ShowGameLevel(Setting::GetGameLevel());

				//for (int i = 0; i < Setting::GetTankNum(); i++)
				//{
				EnemyTank* p1 = new EnemyTank();
				lstTanks.push_back(p1);
				EnemyTank* p2 = new EnemyTank();
				lstTanks.push_back(p2);
				EnemyTank* p3 = new EnemyTank();
				lstTanks.push_back(p3);
				EnemyTank* p4 = new EnemyTank();
				lstTanks.push_back(p4);
				EnemyTank* p5 = new EnemyTank();
				lstTanks.push_back(p5);
				//}

				// 设置暂停，按Enter开始
				skip = true;
				continue;
			}
			/*
			if (mainTank.IsDisappear())
			{
				skip = true;
				bGameOver = true;
				Graphic::ShowGameOver();
				continue;
			}*/

            //判断游戏是否结束
			Rect b = (350, 668, 440, 758);
			for (list<Bullet*>::iterator Eb = EnemyBullets.begin(); Eb != EnemyBullets.end(); Eb++)
				for (list<Bullet*>::iterator Mb = MainBullets.begin(); Mb != MainBullets.end(); Mb++ )
			{
				Rect a = (*Eb)->GetSphere();
				Rect c = (*Mb)->GetSphere();
				if (mainTank.IsDisappear()) //|| Shape::CheckIntersect(a, b) || Shape::CheckIntersect(c,b))
				{
					skip = true;
					bGameOver = true;
					Graphic::ShowGameOver();
					continue;
				}
			}
			mainTank.Move();
			mainTank.Display();

			//初始化一个Tank迭代器，用来实现每一个地方坦克的Move和Display
			//list容器的 end() 函数来得到list末端下一位置
			//相当于：int a[n]中的第n+1个位置a[n]，实际上是不存在的，不能访问。
			for (list<EnemyTank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); )
			{
				(*it)->Move();

				if ((*it)->IsDisappear())
				{
					// Add a bomb
					//(*it)->Boom(lstBombs);
					Setting::TankDamaged();
					// Delete the tank
					delete* it;
					it = lstTanks.erase(it);
					continue;
				}
				(*it)->Display();
				if ((*it)->NeedShoot())
				{
					EnemyTank* p = (*it);
					p->Shoot(EnemyBullets);
				}
				it++;
			}
			for (list<Bullet*>::iterator it = EnemyBullets.begin(); it != EnemyBullets.end();)
			{
				(*it)->Move();

				if ((*it)->IsDisappear())
				{
					//如果消失就爆炸
					//(*it)->bomb(Bombs);
					delete* it;
					it = EnemyBullets.erase(it);
					continue;
				}
				(*it)->Display();
				it++; //不然会溢出
			}
			//初始化一个Bullets迭代器，用来实现子弹的发射
			for (list<Bullet*>::iterator it = MainBullets.begin(); it != MainBullets.end();)
			{
				(*it)->Move();

				if ((*it)->IsDisappear())
				{
					delete* it;
					it = MainBullets.erase(it);
					continue;
				}
				(*it)->Display();
				it++; //不然会溢出
			}

			//墙的实现
			for (list<Barrier*>::iterator it = Barrieies.begin(); it != Barrieies.end();)
			{
				if ((*it)->IsDisappear())
				{
					delete* it;
					it = Barrieies.erase(it);
					continue;
				}
				(*it)->Display();
				it++;
			} 

		}
		Graphic::ShowScore();
		FlushBatchDraw();		// 绘制
		Sleep(200);
	}
	//退出之前养成删除的好习惯
	EndBatchDraw();
	//删除敌方坦克
	for (list<EnemyTank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
	{
		delete* it;
	}
	lstTanks.clear();

	//删除子弹
	for (list<Bullet*>::iterator it = MainBullets.begin(); it != MainBullets.end(); it++)
	{
		delete* it;
	}
	MainBullets.clear();

	//删除爆炸

	Graphic::Destroy();
} 
