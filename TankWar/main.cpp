#pragma warning(disable:4996)

#include <iostream>
#include <conio.h>
#include <time.h>
#include <list>
#include <stdlib.h>


#include "Graphic.h"
#include "MainTank.h"
#include "EnemyTank.h"
#include "EnemyTank.cpp"
#include "Bullet.cpp"
#include "Bomb.h"
#include "Bomb.cpp"
//#include "Utils/Shape.h"
#include "Utils/Shape.cpp"

#define MAX_ENEMYTANKS 5

using namespace std;
IMAGE img;

list<EnemyTank*> lstTanks;
list<Bullet*> MainBullets;
void CheckCrash()
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
int main()
{
	Graphic::Create();
	/*loadimage(&img, L"..\\img\\author.png", 200, 100);
	putimage(200, 300, &img);
	_getch();
	IMAGE img2;
	loadimage(&img2, L"..\\img\\startimg.png",1024,768);
	putimage(0,0, &img2);
	char m;
	m = getchar();
	while (m != 'f' && m != 'F')
		m = getchar();
	*/
	//Tank* eTank[MAX_ENEMYTANKS];
	//用list 进行EenmyTank实现
	lstTanks.clear();

	for (int i = 0; i <= MAX_ENEMYTANKS; i++)
	{
		lstTanks.push_back(new EnemyTank()); //添加一个新坦克
	}
	//子弹的实现：
    //主坦克子弹
	MainBullets.clear();
    
	//爆炸的实现
	list<Bomb*> Bombs;
	Bombs.clear();


	MainTank mainTank;
	bool loop = true;
	bool skip = false;
	while (loop)
	{
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
			CheckCrash();
			Graphic::DrawBattleGround();
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

					// Delete the tank
					delete* it;
					it = lstTanks.erase(it);
					continue;
				}
				(*it)->Display();
				it++;
			}
			//初始化一个Bullets迭代器，用来实现子弹的发射
			for (list<Bullet*>::iterator it = MainBullets.begin(); it != MainBullets.end();)
			{
				(*it)->Move();

				if ((*it)->IsDisappear())
				{
					//如果消失就爆炸
					//(*it)->bomb(Bombs);
					delete* it;
					it = MainBullets.erase(it);
					continue;
				}
				(*it)->Display();
				it++; //不然会溢出
			}

			// 初始化一个Bomb迭代器，用来实现爆炸的消失
			/*for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end();)
			{

				(*it)->Move();  //如何延迟？

				if ((*it)->IsDisappear())
				{
					delete* it;
					it = Bombs.erase(it);
					continue;
				}

				(*it)->Display();
				it++;
			}*/
		}
		Sleep(200);
	}
	//退出之前养成删除的好习惯

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
	for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end(); it++)
	{
		delete* it;
	}
	Bombs.clear();


	Graphic::Destroy();
} 
