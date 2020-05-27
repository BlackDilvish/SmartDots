#include "Population.h"
#include<algorithm>
#include<iostream>

Population::Population(int size)
	: m_population(size)
{
	m_font.loadFromFile("Lato.ttf");

	m_txtGenInfo.setFont(m_font);
	m_txtGenInfo.setString("Generation: 1");
}

void Population::update(const sf::Vector2u& windowSize, const std::vector<Obstacle>& obstacles)
{
	for (auto& dot : m_population)
		if (dot.getStep() < m_bestStep)
			dot.update(windowSize, obstacles);
		else
			dot.kill();

	size_t activeDots = std::count_if(m_population.begin(), m_population.end(), [](Dot& d) { return d.active(); });

	if (activeDots == 0 )
		makeSelection();
}

void Population::render(sf::RenderTarget& target)
{
	for (auto& dot : m_population)
		dot.render(target);
	m_population[0].render(target);

	target.draw(m_txtGenInfo);
}

void Population::makeSelection()
{
	for (auto& dot : m_population)
		dot.calculateFitness();

	m_population[0].setColor(sf::Color::White);
	std::sort(m_population.begin(), m_population.end(), [](Dot& d1, Dot& d2) { return d1.getFitness() > d2.getFitness(); });

	Dot& bestDot = m_population[0];
	std::cout << bestDot.getFitness() << " " << bestDot.getStep() << std::endl;

	if(bestDot.getFitness() > 0.1)
		m_bestStep = bestDot.getStep();
	bestDot.reset();

	for (size_t i=1; i<m_population.size(); i++)
	{
		m_population[i] = bestDot;
		m_population[i].mutate();
	}
	bestDot.setColor(sf::Color::Green);

	m_txtGenInfo.setString("Generation: " + std::to_string(++m_generation));
}
