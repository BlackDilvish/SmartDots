#pragma once

#include<SFML/Graphics.hpp>
#include"Population.h"
#include"Obstacle.h"
#include<iostream>

size_t constexpr POPULATION_SIZE = 1000;

class App
{
public:
	App(const std::pair<size_t, size_t>& windowSize);

	void update();
	void render();

	bool isActive() const;

private:
	void initWindow(const std::pair<size_t, size_t>& windowSize);

	void pollevents();
	void updateClick();
	void setupTarget();
	void setupDots();
	void placeObstacle();
	void moveObstacle();

	bool validClick() const;

	enum class States
	{
		SetupTarget,
		SetupDots,
		Edit,
		Run
	} m_currentState = States::SetupTarget;

	const float m_clickCooldown = 1.f;
	float m_clickTimer = 0;
	sf::Clock m_clock;

	std::unique_ptr<sf::RenderWindow> m_window;

	std::unique_ptr<Population> m_testPopulation;

	std::vector<Obstacle> m_obstacles;
};

