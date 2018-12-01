#include"game.h"


int main()
{
	Direction d = RIGHT;
	Position p(WIDTH / 2, HEIGHT / 2);
	Game *game=new Game(d,p);
	while (!game->IsFialure())
	{
		game->InputDetection();
		game->Check();
		game->Update();
		game->Draw();
	}
	system("CLS");
	cout << "You have failed!!!" << endl;


}