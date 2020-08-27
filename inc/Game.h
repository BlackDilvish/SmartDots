#pragma once

#include<SFML/Graphics.hpp>
#include"Population.h"
#include"Obstacle.h"
#include<iostream>

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
	void handleClick();
	void placeObstacle();
	void moveObstacle();

	bool validClick() const;

	const float m_clickCooldown = 1.f;
	float m_clickTimer = 0;
	sf::Clock m_clock;

	std::unique_ptr<sf::RenderWindow> m_window;

	std::unique_ptr<Population> m_testPopulation{ new Population(POPULATION_SIZE) };

	bool m_editing = false;
	std::vector<Obstacle> m_obstacles;
};

