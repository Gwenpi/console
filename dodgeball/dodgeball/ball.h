#pragma once
#include"color.h"

class Ball
{
private:
	int mx, my;
	char m_Style;
	Color m_Color;
	int m_Life;
public:
	Ball();
	Ball(int x,int y,const char& style,Color color,int life);
	const char& getStyle()const;
	int getX()const;
	int getY()const;
	int& getX();
	int& getY();
	int getLife()const;
	int& getLife();
	Color getColor()const;
	~Ball();
};

