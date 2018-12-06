#include "ball.h"



Ball::Ball()
{
	mx = 20;
	my = 20;
	m_Style = '*';
	m_Color = YELLOW;
	m_Life = 3;
}

Ball::Ball(int x, int y, const char& style, Color color,int left)
	:mx(x),my(y),m_Style(style),m_Color(color),m_Life(left)
{
}

const char& Ball::getStyle()const
{
	return m_Style;
}

int Ball::getX()const
{
	return mx;
}

int Ball::getY()const
{
	return my;
}

int& Ball::getX()
{
	return mx;
}

int& Ball::getY()
{
	return my;
}

int Ball::getLife()const
{
	return m_Life;
}

int & Ball::getLife()
{
	return m_Life;
}

Color Ball::getColor() const
{
	return m_Color;
}

Ball::~Ball()
{
}
