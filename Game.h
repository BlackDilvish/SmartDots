#pragma once

#include<SFML/Graphics.hpp>
#include"Population.h"
#include"Obstacle.h"

size_t constexpr POPULATION_SIZE = 1000;

class Game
{
public:
	Game(const std::pair<size_t, size_t>& windowSize);

	void update();
	void render();

	bool isActive() const;

private:
	void initWindow(const std::pair<size_t, size_t>& windowSize);

	void pollevents();

	std::unique_ptr<sf::RenderWindow> m_window;

	std::unique_ptr<Population> m_testPopulation{ new Population(POPULATION_SIZE) };
	std::vector<Obstacle> m_obstacles;
};

