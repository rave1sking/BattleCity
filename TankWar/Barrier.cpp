#include "Barrier.h"

Barrier::Barrier(Point pos, int Type)
{
	m_pos = pos;
	m_Type = Type;
	m_Disappear = 0;
	CalculateSphere();
}

Barrier::Barrier(int x, int y, int Type)
{
	m_pos.Set(x,y);
	m_Type = Type;
	m_Disappear = 0;
	CalculateSphere();
}


void Barrier::Display()
{
	IMAGE barrier;
	switch (m_Type)
	{
	case 1:
		putimage(m_pos.GetX() - 15, m_pos.GetY() - 15, &barrier1);
		break;
	case 2:
		putimage(m_pos.GetX() - 15, m_pos.GetY() - 15, &barrier2);
		break;
	case 3:
		putimage(m_pos.GetX() - 15, m_pos.GetY() - 15, &barrier3);
		break;
	default:
		break;
	}
}

bool Barrier::IsDisappear()
{
	return m_Disappear;
}

void Barrier::SetDisappear()
{
	m_Disappear = true;
}

void Barrier::CalculateSphere()
{
	  m_rectSphere.Set(m_pos.GetX() - 15, m_pos.GetY() - 15, m_pos.GetX() + 15, m_pos.GetY() + 15);
}

Rect Barrier::GetSphere()
{
	return m_rectSphere;
}

int Barrier::GetTpye()
{
	return m_Type;
}