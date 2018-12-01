#ifndef SNAKE_H
#define SNAKE_H
#include<vector>
#include"food.h"
enum Direction{UP=0,DOWN,LEFT,RIGHT};
struct Body
{
	Direction direction;
	Position position;
	Body(Direction d,Position p) :direction(d),position(p){}
};
class Snake
{
public:
	Snake(){};
	Snake(Direction headD, Position positionD)
	{
		Body head(headD, positionD);
		body.push_back(head);
	}
	bool IsAddBody(Position foodPosition);
	void SetBody(vector<Body> &body);
	void SetHead(Body &head);
	void SetDirection(Direction direction);
	Body GetHead();
	Direction GetDirection();
	vector<Body> GetBody();
	Position GetPosition();
	void show();
private:
	vector<Body>body;
};
void Snake::show()
{
	cout << GetPosition().x << " " << GetPosition().y;
}
bool Snake::IsAddBody(Position foodPosition)
{
	if (GetPosition().x == foodPosition.x&&GetPosition().y == foodPosition.y)
	{
		if (body[body.size() - 1].direction == UP)
		{
			Position position_(body[body.size() - 1].position.x, body[body.size() - 1].position.y + 1);
			Body body_(UP, position_);
			body.push_back(body_);
			
		}
		else if (body[body.size() - 1].direction == DOWN)
		{
			Position position_(body[body.size() - 1].position.x, body[body.size() - 1].position.y - 1);
			Body body_(DOWN, position_);
			body.push_back(body_);
			
		}
		else if (body[body.size() - 1].direction == LEFT)
		{
			Position position_(body[body.size() - 1].position.x + 1, body[body.size() - 1].position.y);
			Body body_(LEFT, position_);
			body.push_back(body_);
			
		}
		else if (body[body.size() - 1].direction == RIGHT)
		{
			Position position_(body[body.size() - 1].position.x - 1, body[body.size() - 1].position.y);
			Body body_(RIGHT, position_);
			body.push_back(body_);
			
		}
		return true;
	}
	return false;
}
void Snake::SetBody(vector<Body> &body)
{
	this->body = body;
}
void Snake::SetHead(Body &head)
{
	body[0] = head;
}
Body Snake::GetHead()
{
	return body[0];
}
void Snake::SetDirection(Direction direction)
{
	body[0].direction = direction;
}
vector<Body> Snake::GetBody()
{
	return body;
}
Position Snake::GetPosition()
{
	return body[0].position;
}
Direction Snake::GetDirection()
{
	return body[0].direction;
}
#endif
