#include "game.h"

#include"interface.h"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

int Current=0;
int Late=0;
int Time=0;

#define MAX_KIND 2		//障碍物种类

Game::Game()
	:m_Time(0.0)
{
	init();
}

void Game::update()
{
	Current = clock();
	Time += Current - Late;
	m_Time += (Current - Late)/1000.0;
	Late = Current;
	
	produceBarrier();
	input();
	barrierChange();
	collisionCheck();
	clearBarrier();


}

void Game::draw()
{
	//player
	gotoxy(player->getX(), player->getY());
	setConsoleColor(player->getColor());
	std::cout << player->getStyle();

	//barrier
	for (int i = 0;i < barrier.size();i++)
	{
		for (int j = 0;j < barrier[i]->getCount();j++)
		{
			gotoxy(barrier[i]->getPosition(j).mx, barrier[i]->getPosition(j).my);
			setConsoleColor(barrier[i]->getColor());
			std::cout << barrier[i]->getStyle();
		}
	}
	//hintInterface
	hintInterface();
}

void Game::produceBarrier()
{
	if (Time / 1000 > 0)
	{
#if 1
		int kind = rand() % MAX_KIND;
		if (0 == kind)
			barrier.push_back(std::unique_ptr<Barrier>(new Barrier(LINE)));//直线
		else if (1 == kind)
#endif
			barrier.push_back(std::unique_ptr<Barrier>(new Barrier(ALASH)));//斜线
		Time -= 50;
	}
}

bool Game::isFailure()const
{
	if (player->getLife() <= 0)
	{
		gotoxy(80, 15);
		std::cout << "you are loser!!!";
		Sleep(2500);
		return true;
	}
	return false;
}

Game::~Game()
{
	delete player;
}

void Game::init()
{
	setWindow(SCR_WIDTH, SCR_HEIGHT);
	hideCursor();
	player=new Ball(SCR_WIDTH / 2, SCR_HEIGHT / 2, '*', YELLOW,3);
	hintInterface();

	srand(time(0));
}

void Game::input()
{
	Sleep(40);
	char ch = '\0';
	if (kbhit())
		ch = getch();
	
	if (ch == 'w')
	{
		if (player->getY() > 0)
		{
			gotoxy(player->getX(), player->getY());
			std::cout << ' ';//将之前绘制的“除去”
			player->getY()--;
		}
	}
	else if(ch == 's')
	{
		if (player->getY() < SCR_HEIGHT)
		{
			gotoxy(player->getX(), player->getY());
			std::cout << ' ';
			player->getY()++;
		}
	}
	else if (ch == 'a')
	{
		if (player->getX() > 0)
		{
			gotoxy(player->getX(), player->getY());
			std::cout << ' ';
			player->getX()--;
		}
	}
	else if (ch == 'd')
	{
		if (player->getX() < SCR_WIDTH)
		{
			gotoxy(player->getX(), player->getY());
			std::cout << ' ';
			player->getX()++;
		}
	}
}

void Game::barrierChange()
{
	
	for (int i = 0;i < barrier.size();i++)
	{
		for (int j = 0;j < barrier[i]->getCount();j++)
		{
			gotoxy(barrier[i]->getPosition(j).mx, barrier[i]->getPosition(j).my);
			std::cout << ' ';//之前输出变空
		}
	}
	for (int i = 0;i < barrier.size();i++)
	{
		Direction d = barrier[i]->getDirection();
		FlightPath fp= barrier[i]->getFlightPath();
		for (int j = 0;j < barrier[i]->getCount();j++)
		{
			if (LINE == fp)
			{
				if (UP == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if(y>0)
						barrier[i]->setPosition(j,x, y - 1);
				}
				else if (DOWN == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if(y<SCR_HEIGHT)
						barrier[i]->setPosition(j, x, y + 1);
				}
				else if (LEFT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if(x>0)
						barrier[i]->setPosition(j, x-1, y);
				}
				else if (RIGHT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if(x<SCR_WIDTH)
						barrier[i]->setPosition(j, x+1, y);
				}
			}
			else if (ALASH == fp)//如果是斜线
			{
				if (UPPER_RIGHT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if (x < SCR_WIDTH && y > 0)
						barrier[i]->setPosition(j, x + 1, y - 1);
				}
				else if (UPPER_LEFT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if (y > 0 && x>0)
						barrier[i]->setPosition(j, x-1, y - 1);
				}
				else if (LOWER_RIGHT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if (x < SCR_WIDTH&&y < SCR_HEIGHT)
						barrier[i]->setPosition(j, x + 1, y + 1);
				}
				else if (LOWER_LEFT == d)
				{
					int x, y;
					barrier[i]->getPosition(j, x, y);
					if (x > 0 && y < SCR_HEIGHT)
						barrier[i]->setPosition(j, x - 1, y + 1);
				}
			}
		}
	}
}

void Game::hintInterface()const
{
	gotoxy(85, 10);
	std::cout << "life: " << player->getLife();
	gotoxy(85, 25);
	std::cout << "time: " << m_Time;
}

void Game::clearBarrier()
{
	for (int i = 0;i < barrier.size();i++)
	{
		int isAll = 0;
		for (int j = 0;j < barrier[i]->getCount();j++)
		{
			if (barrier[i]->getPosition(j).mx == 0 || barrier[i]->getPosition(j).my == 0|| barrier[i]->getPosition(j).mx == SCR_WIDTH || barrier[i]->getPosition(j).my == SCR_HEIGHT)
				isAll++;
		}
		if (isAll == barrier[i]->getCount())
		{
			//delete barrier[i];//这里应该用智能指针才对
			barrier.erase(barrier.begin()+i);
			i--;
		}
	}
}

void Game::collisionCheck()
{
	for (int i = 0;i < barrier.size();i++)
	{
		for (int j = 0;j < barrier[i]->getCount();j++)
		{
			if (barrier[i]->getPosition(j).mx == player->getX() && barrier[i]->getPosition(j).my == player->getY())
			{
				player->getLife()--;
				setConsoleColor(RED);
				gotoxy(player->getX(), player->getY());
				std::cout << '&';
				Sleep(50);
				barrier.erase(barrier.begin() + i);
				i--;
				break;
			}
		}
	}
}
