#pragma once
#include"color.h"
#include<time.h>
#include<iostream>

enum FlightPath { LINE, ALASH, CLOCKWISE };
enum Direction {UP,DOWN,LEFT,RIGHT,UPPER_RIGHT,UPPER_LEFT,LOWER_LEFT,LOWER_RIGHT};

struct Position
{
	int mx;
	int my;
	Position(int x=0, int y=0) :mx(x), my(y) {}
};

class Barrier
{
private:
	Position *m_Position;
	int m_Count;
	char m_Style;
	Color m_Color;
	FlightPath m_FlightPath;//飞行轨迹
	Direction m_Direction;//飞行方向
public:
	Barrier(FlightPath fp = LINE,int number=1,char style='.',Color color=GREEN);
	virtual~Barrier();
	Direction getDirection()const;
	void setDirection(Direction direction);
	Position getPosition(const int& index)const;
	void getPosition(const int& index,int& x, int& y);
	void setPosition(const int& index,const int& x,const int& y);
	int getCount()const;
	char getStyle()const;
	Color getColor()const;
	FlightPath getFlightPath()const;
protected:
	virtual void init();
};

