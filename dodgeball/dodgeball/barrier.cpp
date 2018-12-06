#include "barrier.h"
#include<iostream>

extern int SCR_HEIGHT;
extern int SCR_WIDTH;



Barrier::Barrier(FlightPath fp,int number,char style, Color color)
	:m_FlightPath(fp),m_Count(number),m_Style(style),m_Color(color)
{
	init();
}

void Barrier::init()
{
	Position p1;//初始化x:0,y:0


	int direction = rand() % 4;
	int alashDt = rand() % 2;
	
	if (direction == 0)//初始化位置为上
	{
		p1.my = 1;
		p1.mx = (rand()%SCR_WIDTH-1)+1;
		if (LINE == m_FlightPath)//如果飞行轨迹为直线
		{
			m_Direction = DOWN;//初始化方向为上，所以运动方向为下
		}
		else if (ALASH == m_FlightPath)//飞行轨迹为斜线
		{
			
			if (0 == alashDt)
				m_Direction = LOWER_RIGHT;
			else if (1 == alashDt)
				m_Direction = LOWER_LEFT;
		}
	}
	else if (direction == 1)//下
	{
		p1.my = SCR_HEIGHT-1;
		p1.mx = (rand() % SCR_WIDTH-1)+1;
		if (LINE == m_FlightPath)
			m_Direction = UP;
		else if (ALASH == m_FlightPath)
		{
			if (0 == alashDt)
				m_Direction = UPPER_RIGHT;
			else if (1 == alashDt)
				m_Direction = UPPER_LEFT;
		}
	}
	else if (direction == 2)//左
	{
		p1.mx = 1;
		p1.my = (rand() % SCR_HEIGHT-1)+1;
		if (LINE == m_FlightPath)
			m_Direction = RIGHT;
		else if (ALASH == m_FlightPath)
		{
			if (0 == alashDt)
				m_Direction = UPPER_RIGHT;
			else if (1 == alashDt)
				m_Direction = LOWER_RIGHT;
		}
	}
	else if (direction == 3)//右
	{
		p1.mx = SCR_WIDTH-1;
		p1.my = (rand() % SCR_HEIGHT-1)+1;
		if (LINE == m_FlightPath)
			m_Direction = LEFT;
		else if (ALASH == m_FlightPath)
		{
			if (0 == alashDt)
				m_Direction = UPPER_LEFT;
			else if (1 == alashDt)
				m_Direction = LOWER_LEFT;
		}
	}
	m_Position = new Position[1];
	m_Position[0] = p1;
}

Barrier::~Barrier()
{
	delete[] m_Position;
}

Direction Barrier::getDirection() const
{
	return m_Direction;
}

Position Barrier::getPosition(const int& index) const
{
	return m_Position[index];
}

void Barrier::getPosition(const int& index,int & x, int & y)
{
	x = m_Position[index].mx;
	y = m_Position[index].my;
}

void Barrier::setPosition(const int& index,const int& x, const int& y)
{
	m_Position[index] = Position(x, y);
}

void Barrier::setDirection(Direction direction)
{
	m_Direction = direction;
}

int Barrier::getCount() const
{
	return m_Count;
}

char Barrier::getStyle() const
{
	return m_Style;
}

Color Barrier::getColor() const
{
	return m_Color;
}

FlightPath Barrier::getFlightPath() const
{
	return m_FlightPath;
}


