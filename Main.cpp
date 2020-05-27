#include"Game.h"

int main()
{
	Game game({ 960, 720 });

	while (game.isActive())
	{
		game.update();
		game.render();
	}

	return 0;
}