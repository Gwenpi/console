#include"game.h"
int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

	Game game;
	while (!game.IsFailure())
	{
		game.InputeCheck();
		game.Update();
		game.Draw();
	}
	cout << "��ʧ���ˣ�����" << endl;
	return 0;
}