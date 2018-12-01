#pragma warning (disable:4996)
#include<conio.h>
#include"snake.h"
#include<iostream>
#include<windows.h>

class Game
{
public:
	Game(){};
	Game(Direction d, Position p,bool failure=false) :snake(d, p),isFailure(failure)//初始化蛇头的方向和位置
	{
		do{
			food.RandomFood();
		} while (food.GetPosition().x == snake.GetPosition().x&&food.GetPosition().y == snake.GetPosition().y);
	}
	void Update();
	void InitMaze();
	void InitSnake();
	void InitFood();
	void Draw();
	void InputDetection();//输入检测及处理
	void Check();
	void FoodCheck();//检测是否食屎并产生新的食物
	void CollisionCheck();//碰撞检测
	bool IsFialure();
private:
	bool isFailure;
	Snake snake;
	Food food;
	char maze[HEIGHT][WIDTH];
};
void Game::InitMaze()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || i == (HEIGHT - 1) || j == 0 || j == (WIDTH - 1))
				maze[i][j] = '*';
			else
				maze[i][j] = ' ';
		}
	}
}
void Game::Update()
{
	vector<Body> body = snake.GetBody();
	cout << "长度:" << snake.GetBody().size() << endl;
	for (int i =body.size()-1; i > 0; i--)//蛇身跟随前面的蛇身
	{
		body[i] = body[i-1];
	}
	if (body[0].direction == UP)//最后更新蛇头
		body[0].position.y--;
	else if (body[0].direction == DOWN)
		body[0].position.y++;
	else if (body[0].direction == LEFT)
		body[0].position.x--;
	else if (body[0].direction == RIGHT)
		body[0].position.x++;
	snake.SetBody(body);
}
void Game::InitSnake()
{
	vector<Body>body=snake.GetBody();
	for (int i = 0; i < body.size(); i++)
	{
		maze[body[i].position.y][body[i].position.x] = '@';
	}
}
void Game::InitFood()
{
	maze[food.GetPosition().y][food.GetPosition().x] = '&';
}
void Game::Draw()
{
	Sleep(200);
	system("CLS");
	InitMaze();
	InitSnake();
	InitFood();
	//绘制墙体和蛇和食物
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			cout << maze[i][j];
		cout << endl;
	}
}
void Game::InputDetection()
{
	char ch;
	if (!kbhit())
		ch = ' ';
	else
		ch = getch();
	if (ch=='w')
	{
		if (snake.GetHead().direction != DOWN)
			snake.SetDirection(UP);
	}
	else if (ch == 's')
	{
		if (snake.GetBody()[0].direction != UP)
			snake.SetDirection(DOWN);
	}
	else if (ch == 'a')
	{
		if (snake.GetBody()[0].direction != RIGHT)
			snake.SetDirection(LEFT);
	}
	else if (ch == 'd')
	{
		if (snake.GetBody()[0].direction != LEFT)
			snake.SetDirection(RIGHT);
	}
}
void Game::Check()
{
	FoodCheck();
	CollisionCheck();
}
void Game::FoodCheck()
{
	bool flag = false;
	if (snake.IsAddBody(food.GetPosition()))
	{
		maze[food.GetPosition().x][food.GetPosition().y] = ' ';
		do{
			food.RandomFood();
			for (int i = 0; i < snake.GetBody().size(); i++)
			{
				if (food.GetPosition().x == snake.GetPosition().x&&food.GetPosition().y == snake.GetPosition().y)
				{
					flag = true;
					break;
				}
			}
		} while (flag);

	}
}
void Game::CollisionCheck()
{
	//墙体碰撞检测
	if (snake.GetPosition().x == 0 || snake.GetPosition().x == (WIDTH - 1) || snake.GetPosition().y == (HEIGHT - 1) || snake.GetPosition().y == 0)
	{
		//这里我我把迷宫的宽高与 蛇和食物 的宽高弄反了 可读性变差了（所以在绘图时会把 食物或者蛇 的宽（x） 放入迷宫的高坐标（y））
		
		isFailure = true;
	}
	//身体碰撞检测
	if (snake.GetBody().size() > 4)//长度大于5才有可能发生碰撞
	{
		for (int i = 4; i < snake.GetBody().size(); i++)
		{
			if (snake.GetPosition().x == snake.GetBody()[i].position.x&&snake.GetPosition().y == snake.GetBody()[i].position.y)
			{
				isFailure = true;
			}
		}
	}
}
bool Game::IsFialure()
{
	return isFailure;
}