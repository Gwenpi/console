#pragma warning(disable:4996)
#include"square.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>

#define UP_INTERFACE 3

class Game
{
public:
	Game() :speed(0), speedBase(3),isFailure(false)//这两个数实现了方块下落的速度 流离于 场景绘制之外（及独立于场景）
	{
		InitSquare();
		InitWall();
		Draw();
	}
	~Game()
	{
		delete square;
	}
	void InitSquare();//重新初始化一个方块
	void UpdateSquare();//更新方块位置
	void UpdateVoid(vector<Position> &position);//实块移动过后 更新空白块
	void InitWall();
	void Draw();
	void Update();
	void InputeCheck();//输入检查
	bool SideCollisionDetection(vector<Position> &position);//墙体碰撞检测
	bool LeftCollisionDetection(vector<Position> &position);//左实体碰撞检测 
	bool RightCollisionDetection(vector<Position> &position);//右实体碰撞检测  碰撞返回true
	bool BottomCollisionDetection(vector<Position> &position);//底边触碰（如果位置与底边重合则返回true）
	bool NSquareCollisionDetection(vector<Position> &position);// 预判下一个 砖块碰撞检测
	bool CSquareCollisionDetection(vector<Position> &beforePosition,vector<Position> &changePosition);//变化 砖块碰撞检测
	void EliminateCheck();//消除检查
	bool IsWall(Position position);//判断当前出是否为墙，墙体的数据最后重置
	bool IsFailure();//判断是否失败
private:
	Square *square=NULL;
	int interface_[HEIGHT][WIDTH];//游戏界面
	int speed;//方块下落速度
	int speedBase;//下落的基数
	bool isFailure;
};
void Game::InitWall()
{
	for (int i = 0; i != HEIGHT; i++)
	{
		for (int j = 0; j != WIDTH; j++)
		{
			//用“1”表示墙体方块,“0”表示空,"2"表示实体方块
			if (i == UP_INTERFACE || i == (HEIGHT - 1) || (j == 0 && i > (UP_INTERFACE - 1)) || (j == (WIDTH - 1) && i > (UP_INTERFACE - 1)))
				interface_[i][j] = 1;
			else if (interface_[i][j]!=2)//当所属位置不是 实块和墙体 时绘制空白
				interface_[i][j] = 0;
		}
	}
}
void Game::InitSquare()
{
	//随机一个方块
	srand(static_cast<unsigned int>(time(0)));
	int aRand = rand() % 5;
	if (aRand == 0)
	{
		square = new Square_1();
		cout << square->GetTransform();
	}
	else if (aRand == 1)
	{
		square = new Square_2();
		cout << square->GetTransform();
	}
	else if (aRand == 2)
	{
		square = new Square_3();
		cout << square->GetTransform();
	}
	else if (aRand == 3)
	{
		square = new Square_4();
		cout << square->GetTransform();
	}
	else if (aRand == 4)
	{
		square = new Square_5();
		cout << square->GetTransform();
	}
}
void Game::UpdateSquare()
{
	//将更新后的方块重新放入场景
	for (int i = 0; i != square->GetSquare().size(); i++)
	{
		int line = square->GetSquare()[i].line;
		int column = square->GetSquare()[i].column;
		interface_[line][column] = 2;
	}
}
void Game::UpdateVoid(vector<Position> &position)
{
	for (int i = 0; i < position.size(); i++)
		interface_[position[i].line][position[i].column] = 0;//将之前的位置方块置为空白
}
void Game::Draw()
{
	Sleep(50);//更新的频率（等待时间）
	system("CLS");//这里 先等待再清屏  与 先清屏再等待 效果不同（后者会使得画面不连贯（你应该懂得））
	UpdateSquare();
	InitWall();
	for (int i = 0; i != HEIGHT; i++)
	{
		for (int j = 0; j != WIDTH; j++)
		{
			if (interface_[i][j] == 0)
				cout << "  ";
			else if (interface_[i][j] == 1)
				cout << '\22';
			else if (interface_[i][j] == 2)
				cout << '\22';
		}
		cout << '\n';
	}
}
void Game::Update()
{
	if (speed % speedBase == 0)
	{
		if (!NSquareCollisionDetection(square->GetSquare()))//如果下一个位置是实块和墻體
		{
			vector<Position> square_;
			for (int i = 0; i != square->GetSquare().size(); i++)
			{
				if (speed % speedBase == 0)
				{
					Position position;
					position.line = square->GetSquare()[i].line + 1;
					position.column = square->GetSquare()[i].column;
					square_.push_back(position);
				}
			}
			UpdateVoid(square->GetSquare());//将之前的 实块 更新为 空白块
			square->SetAllSquare(square_);//设置现在的方块
			
		}
		else//否则冻结现在位置 并 随机一个方块
		{
			for (int i = 0; i != square->GetSquare().size(); i++)
			{
				if (!IsWall(square->GetSquare()[i]))
					interface_[square->GetSquare()[i].line][square->GetSquare()[i].column] = 2;
				else
				{
					interface_[square->GetSquare()[i].line][square->GetSquare()[i].column] = 2;
					isFailure = true;
				}
			}
			delete square;
			InitSquare();
			EliminateCheck();
		}
	}
	speed++;
}
void Game::InputeCheck()
{
	char ch;
	if (!kbhit())
		ch = ' ';
	else
		ch = getch();
	if (ch == 'w')//变化方块(重置空白块，是否可以 边界变化)（未完善）
	{
		square->AddTransform();
		vector<Position> changePosition = square->CurrentTransform();
		if (!SideCollisionDetection(changePosition) && !BottomCollisionDetection(changePosition) && !CSquareCollisionDetection(square->GetSquare(),changePosition))
		{
			UpdateVoid(square->GetSquare());
			square->SetAllSquare(changePosition);
		}
	}
	else if (ch == 'a')//向左移动
	{
		vector<Position>square_;
		for (int i = 0; i != square->GetSquare().size(); i++)
		{
			Position position;
			position.line = square->GetSquare()[i].line;
			position.column = square->GetSquare()[i].column - 1;
			square_.push_back(position);
		}
		if (!SideCollisionDetection(square_)&&!LeftCollisionDetection(square_))
		{
			UpdateVoid(square->GetSquare());
			square->SetAllSquare(square_);//设置现在的方块
		}
	}
	else if (ch == 'd')//向右移动
	{
		vector<Position>square_;
		for (int i = 0; i != square->GetSquare().size(); i++)
		{
			Position position;
			position.line = square->GetSquare()[i].line;
			position.column = square->GetSquare()[i].column + 1;
			square_.push_back(position);
		}
		if (!SideCollisionDetection(square_) && !RightCollisionDetection(square_))
		{
			UpdateVoid(square->GetSquare());
			square->SetAllSquare(square_);//设置现在的方块
		}
	}
	else if (ch == 's')//快速落地
	{
		if (!NSquareCollisionDetection(square->GetSquare()))
		{
			vector<Position>square_;
			for (int i = 0; i != square->GetSquare().size(); i++)
			{
				Position position;
				position.line = square->GetSquare()[i].line + 1;
				position.column = square->GetSquare()[i].column;
				square_.push_back(position);
			}
			UpdateVoid(square->GetSquare());
			square->SetAllSquare(square_);//设置现在的方块
		}
	}
}
bool Game::SideCollisionDetection(vector<Position> &position)
{
	for (int i = 0; i != position.size(); i++)
	{
		if (position[i].column == 0 || position[i].column == (WIDTH - 1))//左右墙体的检测
		{
			return true;
		}
		
	}	
	return false;
}
bool Game::LeftCollisionDetection(vector<Position> &position)
{
	//判断方块 最左 或 最右 的实块
	vector<Position>leftPosition;
	for (int i = 0; i != position.size(); i++)
	{
		Position side = position[i];
		bool leftJudge = true;
		for (int j = 0; j != position.size(); j++)
		{
			if (i != j&&side.line == position[j].line)
			{
				if (side.column > position[j].column)
				{
					leftJudge=false;
					break;
				}
			}
		}
		if (leftJudge)
		{
			leftPosition.push_back(side);
		}
	}
	for (int i = 0; i != leftPosition.size(); i++)
	{
		if (interface_[leftPosition[i].line][leftPosition[i].column] == 2)
		{
			return true;
		}
	}
	return false;
}
bool Game::RightCollisionDetection(vector<Position> &position)
{
	//判断方块 最左 或 最右 的实块
	vector<Position>rightPosition;
	for (int i = 0; i != position.size(); i++)
	{
		Position side = position[i];
		bool rightJudge = true;
		for (int j = 0; j != position.size(); j++)
		{
			if (i != j&&side.line == position[j].line)
			{
				if (side.column < position[j].column)
				{
					rightJudge = false;
					break;
				}
			}
		}
		if (rightJudge)
		{
			rightPosition.push_back(side);
		}
	}
	for (int i = 0; i != rightPosition.size(); i++)
	{
		if (interface_[rightPosition[i].line][rightPosition[i].column] == 2)
		{
			return true;
		}
	}
	return false;
}
bool Game::BottomCollisionDetection(vector<Position> &position)
{
	for (int i = 0; i != position.size(); i++)
	{
		if (position[i].line == (HEIGHT - 1))//触底检测
		{
			return true;
		}
	}
	return false;
}
bool Game::NSquareCollisionDetection(vector<Position> &position)//这里是根据方块的最下一行判断（这里要改成根据当前列的最下一行）
{
	vector<Position>bottomPosition;
	for (int j = 0; j != position.size(); j++)
	{
		Position bottom = position[j];
		int flag = true;
		for (int i = 0; i != position.size(); i++)
		{
			if (j != i&&bottom.column == position[i].column)
			{
				if (bottom.line < position[i].line)
				{
					flag = false;
					break;
				}
			}
		}
		if (flag)//如果是 当前列 的 最小行
		{
			bottomPosition.push_back(bottom);
		}
	}
	//cout << bottomPosition.size();
	for (int i = 0; i != bottomPosition.size(); i++)
	{
		if (interface_[bottomPosition[i].line + 1][bottomPosition[i].column] == 2 || bottomPosition[i].line + 1 == (HEIGHT - 1))//如果下一行是实块(这里要防止方块之间的自行判断)
		{
			return true;
		}
	}
	return false;
}
bool Game::CSquareCollisionDetection(vector<Position> &beforePosition, vector<Position> &changePosition)
{
	vector<Position>position;
	//先判断哪些方块发生了改变
	for (int i = 0; i != changePosition.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j != beforePosition.size(); j++)
		{
			if (beforePosition[j].line != changePosition[i].line&&beforePosition[j].column != changePosition[i].column)
			{
				flag++;
			}
		}
		if (flag == beforePosition.size())
			position.push_back(changePosition[i]);
	}
	for (int i = 0; i != position.size(); i++)
	{
		if (interface_[position[i].line][position[i].column] == 2)//如果改变后的位置上有实块
		{
			return true;
		}
	}
	return false;
}
void Game::EliminateCheck()//mark
{
	vector<int> eliminateArray;
	int eliminateLine;
	bool isEliminate;
	for (int j = HEIGHT - 2; j != UP_INTERFACE; j--)
	{
		eliminateLine=j;//记录这行
		isEliminate = true;
		for (int i = WIDTH - 2; i != 0; i--)
		{
			if (interface_[j][i] != 2)
			{
				isEliminate = false;
				break;
			}
		}
		if (isEliminate)//如果这行可以消除
		{
			eliminateArray.push_back(eliminateLine);//加入消除数组
		}
	}
	int eliminateAmount = 0;//已经消除行的总数数(因为我这里设定每次消除一行，所以当下移一行时，消除行也要下移一行，以免消错行)
	for (int j = 0; j != eliminateArray.size(); j++)
	{
		for (int i = 1; i != WIDTH - 1; i++)//消除这行
			interface_[eliminateArray[j]+eliminateAmount][i] = 0;
		for (int l = eliminateArray[j] + eliminateAmount; l != (UP_INTERFACE + 1); l--)//以上的每行下移一层（这里以空白行的第二行为上界）
		{
			for (int c = 1; c != WIDTH - 1; c++)
			{
				interface_[l][c] = interface_[l - 1][c];//以消除行为界，场景下移一行
			}
		}
		if (j + 1 != eliminateArray.size())//如果下一行还有消除的Line
		{
			eliminateAmount++;
		}
	}
}
bool Game::IsWall(Position position)//这种判断就必须 让 初始化墙体 在 更新方块位置 之后（因为这样就可以一直保持 上界墙体的数据永远在 更新方块之前存在 这样就可以让胜负判断完美判断 避免BUG）
{
	if (interface_[position.line][position.column] == 1)//如果与墙体碰撞
	{
		return true;
	}
	else
		return false;
	cout << "此处不是墙体和空白块!!";
}
bool Game::IsFailure()
{
	return isFailure;
}