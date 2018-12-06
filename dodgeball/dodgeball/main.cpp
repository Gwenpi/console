
#include"game.h"

int SCR_WIDTH = 80;
int SCR_HEIGHT = 40; 

using std::cout;
using std::endl;


int main()
{
	Game game;
	while (!game.isFailure())
	{
		game.update();
		game.draw();
	}
	system("PAUSE");
	return 0;
}