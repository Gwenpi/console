#ifndef FOOD_H
#define FOOD_H

#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;

static const int WIDTH = 50, HEIGHT = 20;

struct  Position
{
	int x, y;
	Position(int x_=0, int y_=0) :x(x_), y(y_){}
};
class Food
{
public:
	Food():position()
	{
		srand(static_cast<unsigned int>(time(0))); 
	}
	void RandomFood();//随机食物的位置
	Position GetPosition();
	void show();
private:
	Position position;
};
void Food::RandomFood()
{
	position.x = 1 + rand() % (WIDTH-2);
	position.y = 1 + rand() % (HEIGHT-2);
}
Position Food::GetPosition()
{
	return position;
}
void Food::show()
{
	cout << position.x << " " << position.y << endl;
}
#endif