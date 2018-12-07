#include"game.h"
int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

	Game game;
	while (!game.IsFailure())
	{
		game.InputeCheck();
		game.Update();
		game.Draw();
	}
	cout << "你失败了！！！" << endl;
	return 0;
}