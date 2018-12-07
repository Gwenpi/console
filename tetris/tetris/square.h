#include<vector>
#include<random>
#include<time.h>
using namespace std;

const int WIDTH = 20, HEIGHT = 25+4;//这里我设置了一个高为4的预备区域（因为长条型方块初始占高4）

struct Position{
	int line, column;
	Position() :line(0), column(0){}
	Position(int l, int c) :line(l), column(c){}
};

class Square
{
public:
	virtual vector<Position> CurrentTransform()=0;//变化当前所对应的位置（顺时针变化）
	void InitTransform();
	int GetTransform();
	void SetTransform(int transform);
	void AddTransform();
	void AddSquare(Position p);
	void SetSquare(Position p, int index);
	void SetAllSquare(vector<Position> &position);
	vector<Position> GetSquare();
	void InitSetCenterPosition(Position center);
	Position GetCenterPosition();//中心位置为square[0]
private:
	int transform;//变化的基数
	vector<Position>square;
};
int Square::GetTransform()
{
	return transform;
}
void Square::SetTransform(int transform)
{
	this->transform = transform;
}
void Square::AddTransform()
{
	transform++;
}
void Square::AddSquare(Position p)
{
	square.push_back(p);
}
void Square::SetSquare(Position p, int index)
{
	square[index] = p;
}
void Square::SetAllSquare(vector<Position> &position)
{
	square = position;
}
vector<Position> Square::GetSquare()
{
	return square;
}
void Square::InitTransform()
{
	srand(static_cast<unsigned int>(time(0)));
	int transform_ = rand() % 4;
	this->transform = transform_;
}
void Square::InitSetCenterPosition(Position center)
{
	square.push_back(Position());
	square[0] = center;
}
Position Square::GetCenterPosition()
{
	return square[0];
}
//“山”型方块
class Square_1:public Square
{
public:
	Square_1()
	{
		Position center(3, WIDTH / 2);
		Position left(3, WIDTH / 2 - 1);
		Position top(2, WIDTH / 2);
		Position right(3, WIDTH / 2 + 1);
		InitTransform();//随机基数
		InitSetCenterPosition(center);
		AddSquare(left);
		AddSquare(top);
		AddSquare(right);
		SetAllSquare(CurrentTransform());//应用当前基数设置方块方向
	}
	virtual vector<Position> CurrentTransform();//砖块的变换
};
vector<Position> Square_1::CurrentTransform()
{
	vector<Position>position;
	if (GetTransform() % 4 == 0)
	{
		Position center = GetCenterPosition();
		Position top(center.line - 1, center.column);
		Position right(center.line, center.column + 1);
		Position left(center.line, center.column - 1);
		position.push_back(center);
		position.push_back(top);
		position.push_back(right);
		position.push_back(left);
	}
	else if (GetTransform() % 4 == 1)
	{
		Position center = GetCenterPosition();
		Position top(center.line - 1, center.column);
		Position right(center.line, center.column + 1);
		Position bottom(center.line + 1, center.column);
		position.push_back(center);
		position.push_back(top);
		position.push_back(right);
		position.push_back(bottom);
	}
	else if (GetTransform() % 4 == 2)
	{
		Position center = GetCenterPosition();
		Position left(center.line, center.column-1);
		Position right(center.line, center.column + 1);
		Position bottom(center.line + 1, center.column);
		position.push_back(center);
		position.push_back(left);
		position.push_back(right);
		position.push_back(bottom);
	}
	else if (GetTransform() % 4 == 3)
	{
		Position center = GetCenterPosition();
		Position top(center.line - 1, center.column);
		Position left(center.line, center.column - 1);
		Position bottom(center.line + 1, center.column);
		position.push_back(center);
		position.push_back(top);
		position.push_back(left);
		position.push_back(bottom);
	}
	return position;
}
//“L”型方块
class Square_2:public Square
{
public:
	Square_2()
	{
		Position center(3, WIDTH / 2);
		Position left(3, WIDTH / 2 - 1);
		Position right(3, WIDTH / 2 + 1);
		Position top_right(2, WIDTH / 2 + 1);
		InitTransform();
		InitSetCenterPosition(center);
		AddSquare(left);
		AddSquare(right);
		AddSquare(top_right);
		SetAllSquare(CurrentTransform());
	}
	virtual vector<Position> CurrentTransform();
};
vector<Position> Square_2::CurrentTransform()
{
	vector<Position>position;
	if (GetTransform() % 4 == 0)
	{
		Position center = GetCenterPosition();
		Position left(center.line, center.column - 1);
		Position right(center.line, center.column + 1);
		Position top_right(center.line - 1, center.column + 1);
		position.push_back(center);
		position.push_back(left);
		position.push_back(right);
		position.push_back(top_right);
	}
	else if (GetTransform() % 4 == 1)
	{
		Position center = GetCenterPosition();
		Position top(center.line - 1, center.column);
		Position bottom(center.line + 1, center.column);
		Position bottom_right(center.line + 1, center.column + 1);
		position.push_back(center);
		position.push_back(top);
		position.push_back(bottom);
		position.push_back(bottom_right);
	}
	else if (GetTransform() % 4 == 2)
	{
		Position center = GetCenterPosition();
		Position left(center.line, center.column - 1);
		Position right(center.line, center.column + 1);
		Position bottom_left(center.line + 1, center.column - 1);
		position.push_back(center);
		position.push_back(left);
		position.push_back(right);
		position.push_back(bottom_left);
	}
	else if (GetTransform() % 4 == 3)
	{
		Position center = GetCenterPosition();
		Position top_left(center.line - 1, center.column - 1);
		Position top(center.line - 1, center.column);
		Position bottom(center.line + 1, center.column);
		position.push_back(center);
		position.push_back(top_left);
		position.push_back(top);
		position.push_back(bottom);
	}
	return position;
}
//“Z”型方块
class Square_3 :public Square
{
public:
	Square_3()
	{
		Position center(2, WIDTH / 2);
		Position left(2, WIDTH / 2 - 1);
		Position bottom(3, WIDTH / 2);
		Position top_right(3, WIDTH / 2 + 1);
		InitTransform();
		InitSetCenterPosition(center);
		AddSquare(left);
		AddSquare(bottom);
		AddSquare(top_right);
		SetAllSquare(CurrentTransform());
	}
	virtual vector<Position> CurrentTransform();
	virtual void InitTransform()
	{
		srand(static_cast<unsigned int>(time(0)));
		int transform = rand() % 2;
		SetTransform(transform);
	}
};
vector<Position> Square_3::CurrentTransform()
{
	vector<Position>position;
	if (GetTransform() % 2 == 0)
	{
		Position center = GetCenterPosition();
		Position left(center.line, center.column - 1);
		Position bottom(center.line + 1, center.column);
		Position bottom_right(center.line + 1, center.column + 1);
		position.push_back(center);
		position.push_back(left);
		position.push_back(bottom);
		position.push_back(bottom_right);
	}
	else if (GetTransform() % 2 == 1)
	{
		Position center = GetCenterPosition();
		Position top(center.line - 1, center.column);
		Position left(center.line, center.column - 1);
		Position bottom_left(center.line + 1, center.column - 1);
		position.push_back(center);
		position.push_back(top);
		position.push_back(left);
		position.push_back(bottom_left);
	}
	return position;
}
//“L”型方块
class Square_4 :public Square
{
public:
	Square_4()
	{
		Position center(2, WIDTH / 2);
		Position top_top(0, WIDTH / 2);
		Position top(1, WIDTH / 2 );
		Position bottom(3, WIDTH / 2);
		InitTransform();
		InitSetCenterPosition(center);
		AddSquare(top_top);
		AddSquare(top);
		AddSquare(bottom);
	}
	virtual vector<Position> CurrentTransform();
};
vector<Position> Square_4::CurrentTransform()
{
	vector<Position>position;
	if (GetTransform() % 2 == 0)
	{
		Position center = GetCenterPosition();
		Position top_top(center.line - 2, center.column);
		Position top(center.line - 1, center.column);
		Position bottom(center.line + 1, center.column);
		position.push_back(center);
		position.push_back(top_top);
		position.push_back(top);
		position.push_back(bottom);
	}
	else if (GetTransform() % 2 == 1)
	{
		Position center = GetCenterPosition();
		Position left_left(center.line, center.column - 2);
		Position left(center.line, center.column - 1);
		Position right(center.line, center.column + 1);
		position.push_back(center);
		position.push_back(left_left);
		position.push_back(left);
		position.push_back(right);
	}
	return position;
}
//“田”字型方块
class Square_5 :public Square
{
public:
	Square_5()
	{
		Position center(2, WIDTH / 2);
		Position right(2, WIDTH / 2 + 1);
		Position bottom(3, WIDTH / 2);
		Position bottom_right(3, WIDTH / 2 + 1);
		InitTransform();
		InitSetCenterPosition(center);
		AddSquare(right);
		AddSquare(bottom);
		AddSquare(bottom_right);
	}
	virtual vector<Position> CurrentTransform();
};
vector<Position> Square_5::CurrentTransform()
{
	return GetSquare();
}
