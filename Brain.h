#pragma once

#include<vector>
#include<SFML/Graphics.hpp>

template<typename T, typename U>
inline auto randNum(T a, U b) { return (static_cast<float>(std::rand()) / (RAND_MAX)) * (b-a) + a; }

struct Brain
{
	Brain(int size);

	void mutate();

	std::vector<sf::Vector2f> directions;
	size_t step = 0;
	static const int mutationRate;
};

