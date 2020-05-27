#include "Brain.h"

Brain::Brain(int size)
	: directions(size)
{
	for (auto& dir : directions)
		dir = { randFloat(), randFloat() };
}

void Brain::mutate()
{
	for (auto& dir : directions)
		if((std::rand() % 100) < Brain::mutationRate)
			dir = { randFloat(), randFloat() };
}

const int Brain::mutationRate = 1;
