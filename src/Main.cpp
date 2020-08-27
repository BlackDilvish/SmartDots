#include"App.h"

int main()
{
	App app({ 960, 720 });

	while (app.isActive())
	{
		app.update();
		app.render();
	}

	return 0;
}