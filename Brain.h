#pragma once

#include<vector>
#include<SFML/Graphics.hpp>

inline float randFloat() { return ((float)std::rand() / (RAND_MAX)) * 2 - 1; }

struct Brain
{
	Brain(int size);

	void mutate();

	std::vector<sf::Vector2f> directions;
	size_t step = 0;
	static const int mutationRate;
};

