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

#define MAX_ENEMYTANKS 5

using namespace std;
IMAGE img;


int main()
{
	Graphic::Create();
	//MAGE img;
	loadimage(&img, L"..\\img\\author.png", 200, 100);
	putimage(200, 300, &img);
	_getch();
	IMAGE img2;
	loadimage(&img2, L"..\\img\\startimg.png",1024,768);
	putimage(0,0, &img2);
	char m;
	m = getchar();
	while (m != 'f' && m != 'F')
		m = getchar();

	//Tank* eTank[MAX_ENEMYTANKS];
	//用list 进行EenmyTank实现
	list<EnemyTank*> lstTanks;
	lstTanks.clear();

	for (int i = 0; i < MAX_ENEMYTANKS; i++)
	{
		lstTanks.push_back(new EnemyTank()); //添加一个新坦克
	}
	//子弹的实现：
	list<Bullet*> Bullets;
	Bullets.clear();
    
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
				mainTank.Shoot(Bullets);
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
			Graphic::DrawBattleGround();
			mainTank.Move();
			mainTank.Display();

			//初始化一个Tank迭代器，用来实现每一个坦克的Move和Display
			for (list<EnemyTank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
			{
				(*it)->Move();
				(*it)->Display();
			}
			//初始化一个Bullets迭代器，用来实现子弹的发射
			for (list<Bullet*>::iterator it = Bullets.begin(); it != Bullets.end();)
			{
				(*it)->Move();

				if ((*it)->IsDisappear())
				{
					//如果消失就爆炸
					(*it)->bomb(Bombs);
					delete* it;
					it = Bullets.erase(it);
					continue;
				}

				(*it)->Display();
				it++;
			}

			// 初始化一个Bomb迭代器，用来实现爆炸的消失
			for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end();)
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
			}
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
	for (list<Bullet*>::iterator it = Bullets.begin(); it != Bullets.end(); it++)
	{
		delete* it;
	}
	Bullets.clear();

	//删除爆炸
	for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end(); it++)
	{
		delete* it;
	}
	Bombs.clear();


	Graphic::Destroy();
} 
