#pragma once

#include<vector>
#include"Dot.h"
#include"Obstacle.h"

class Population
{
public:
	Population(int size);

	void update(const sf::Vector2u& windowSize, const std::vector<Obstacle>& obstacles);
	void render(sf::RenderTarget& target);

private:
	void makeSelection();
	int poolSelection();

	size_t m_generation = 1;
	size_t m_bestStep = BRAIN_SIZE;
	std::vector<Dot> m_population;

	sf::Font m_font;
	sf::Text m_txtGenInfo;

};

