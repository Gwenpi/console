#pragma warning(disable:4996)
#include"square.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>

#define UP_INTERFACE 3

class Game
{
public:
	Game() :speed(0), speedBase(3),isFailure(false)//��������ʵ���˷���������ٶ� ������ ��������֮�⣨�������ڳ�����
	{
		InitSquare();
		InitWall();
		Draw();
	}
	~Game()
	{
		delete square;
	}
	void InitSquare();//���³�ʼ��һ������
	void UpdateSquare();//���·���λ��
	void UpdateVoid(vector<Position> &position);//ʵ���ƶ����� ���¿հ׿�
	void InitWall();
	void Draw();
	void Update();
	void InputeCheck();//������
	bool SideCollisionDetection(vector<Position> &position);//ǽ����ײ���
	bool LeftCollisionDetection(vector<Position> &position);//��ʵ����ײ��� 
	bool RightCollisionDetection(vector<Position> &position);//��ʵ����ײ���  ��ײ����true
	bool BottomCollisionDetection(vector<Position> &position);//�ױߴ��������λ����ױ��غ��򷵻�true��
	bool NSquareCollisionDetection(vector<Position> &position);// Ԥ����һ�� ש����ײ���
	bool CSquareCollisionDetection(vector<Position> &beforePosition,vector<Position> &changePosition);//�仯 ש����ײ���
	void EliminateCheck();//�������
	bool IsWall(Position position);//�жϵ�ǰ���Ƿ�Ϊǽ��ǽ��������������
	bool IsFailure();//�ж��Ƿ�ʧ��
private:
	Square *square=NULL;
	int interface_[HEIGHT][WIDTH];//��Ϸ����
	int speed;//���������ٶ�
	int speedBase;//����Ļ���
	bool isFailure;
};
void Game::InitWall()
{
	for (int i = 0; i != HEIGHT; i++)
	{
		for (int j = 0; j != WIDTH; j++)
		{
			//�á�1����ʾǽ�巽��,��0����ʾ��,"2"��ʾʵ�巽��
			if (i == UP_INTERFACE || i == (HEIGHT - 1) || (j == 0 && i > (UP_INTERFACE - 1)) || (j == (WIDTH - 1) && i > (UP_INTERFACE - 1)))
				interface_[i][j] = 1;
			else if (interface_[i][j]!=2)//������λ�ò��� ʵ���ǽ�� ʱ���ƿհ�
				interface_[i][j] = 0;
		}
	}
}
void Game::InitSquare()
{
	//���һ������
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
	//�����º�ķ������·��볡��
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
		interface_[position[i].line][position[i].column] = 0;//��֮ǰ��λ�÷�����Ϊ�հ�
}
void Game::Draw()
{
	Sleep(50);//���µ�Ƶ�ʣ��ȴ�ʱ�䣩
	system("CLS");//���� �ȵȴ�������  �� �������ٵȴ� Ч����ͬ�����߻�ʹ�û��治���ᣨ��Ӧ�ö��ã���
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
		if (!NSquareCollisionDetection(square->GetSquare()))//�����һ��λ����ʵ��͉��w
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
			UpdateVoid(square->GetSquare());//��֮ǰ�� ʵ�� ����Ϊ �հ׿�
			square->SetAllSquare(square_);//�������ڵķ���
			
		}
		else//���򶳽�����λ�� �� ���һ������
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
	if (ch == 'w')//�仯����(���ÿհ׿飬�Ƿ���� �߽�仯)��δ���ƣ�
	{
		square->AddTransform();
		vector<Position> changePosition = square->CurrentTransform();
		if (!SideCollisionDetection(changePosition) && !BottomCollisionDetection(changePosition) && !CSquareCollisionDetection(square->GetSquare(),changePosition))
		{
			UpdateVoid(square->GetSquare());
			square->SetAllSquare(changePosition);
		}
	}
	else if (ch == 'a')//�����ƶ�
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
			square->SetAllSquare(square_);//�������ڵķ���
		}
	}
	else if (ch == 'd')//�����ƶ�
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
			square->SetAllSquare(square_);//�������ڵķ���
		}
	}
	else if (ch == 's')//�������
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
			square->SetAllSquare(square_);//�������ڵķ���
		}
	}
}
bool Game::SideCollisionDetection(vector<Position> &position)
{
	for (int i = 0; i != position.size(); i++)
	{
		if (position[i].column == 0 || position[i].column == (WIDTH - 1))//����ǽ��ļ��
		{
			return true;
		}
		
	}	
	return false;
}
bool Game::LeftCollisionDetection(vector<Position> &position)
{
	//�жϷ��� ���� �� ���� ��ʵ��
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
	//�жϷ��� ���� �� ���� ��ʵ��
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
		if (position[i].line == (HEIGHT - 1))//���׼��
		{
			return true;
		}
	}
	return false;
}
bool Game::NSquareCollisionDetection(vector<Position> &position)//�����Ǹ��ݷ��������һ���жϣ�����Ҫ�ĳɸ��ݵ�ǰ�е�����һ�У�
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
		if (flag)//����� ��ǰ�� �� ��С��
		{
			bottomPosition.push_back(bottom);
		}
	}
	//cout << bottomPosition.size();
	for (int i = 0; i != bottomPosition.size(); i++)
	{
		if (interface_[bottomPosition[i].line + 1][bottomPosition[i].column] == 2 || bottomPosition[i].line + 1 == (HEIGHT - 1))//�����һ����ʵ��(����Ҫ��ֹ����֮��������ж�)
		{
			return true;
		}
	}
	return false;
}
bool Game::CSquareCollisionDetection(vector<Position> &beforePosition, vector<Position> &changePosition)
{
	vector<Position>position;
	//���ж���Щ���鷢���˸ı�
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
		if (interface_[position[i].line][position[i].column] == 2)//����ı���λ������ʵ��
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
		eliminateLine=j;//��¼����
		isEliminate = true;
		for (int i = WIDTH - 2; i != 0; i--)
		{
			if (interface_[j][i] != 2)
			{
				isEliminate = false;
				break;
			}
		}
		if (isEliminate)//������п�������
		{
			eliminateArray.push_back(eliminateLine);//������������
		}
	}
	int eliminateAmount = 0;//�Ѿ������е�������(��Ϊ�������趨ÿ������һ�У����Ե�����һ��ʱ��������ҲҪ����һ�У�����������)
	for (int j = 0; j != eliminateArray.size(); j++)
	{
		for (int i = 1; i != WIDTH - 1; i++)//��������
			interface_[eliminateArray[j]+eliminateAmount][i] = 0;
		for (int l = eliminateArray[j] + eliminateAmount; l != (UP_INTERFACE + 1); l--)//���ϵ�ÿ������һ�㣨�����Կհ��еĵڶ���Ϊ�Ͻ磩
		{
			for (int c = 1; c != WIDTH - 1; c++)
			{
				interface_[l][c] = interface_[l - 1][c];//��������Ϊ�磬��������һ��
			}
		}
		if (j + 1 != eliminateArray.size())//�����һ�л���������Line
		{
			eliminateAmount++;
		}
	}
}
bool Game::IsWall(Position position)//�����жϾͱ��� �� ��ʼ��ǽ�� �� ���·���λ�� ֮����Ϊ�����Ϳ���һֱ���� �Ͻ�ǽ���������Զ�� ���·���֮ǰ���� �����Ϳ�����ʤ���ж������ж� ����BUG��
{
	if (interface_[position.line][position.column] == 1)//�����ǽ����ײ
	{
		return true;
	}
	else
		return false;
	cout << "�˴�����ǽ��Ϳհ׿�!!";
}
bool Game::IsFailure()
{
	return isFailure;
}