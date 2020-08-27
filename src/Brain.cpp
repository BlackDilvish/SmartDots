#include "Brain.h"

Brain::Brain(int size)
	: directions(size)
{
	for (auto& dir : directions)
		dir = { randNum(-1, 1), randNum(-1, 1) };
}

void Brain::mutate()
{
	for (auto& dir : directions)
		if((std::rand() % 100) < Brain::mutationRate)
			dir = { randNum(-1, 1), randNum(-1, 1) };
}

const int Brain::mutationRate = 1;
