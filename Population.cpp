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

	if(bestDot.finished())
		m_bestStep = bestDot.getStep();


	float sum = 0;
	for (const auto& p : m_population)
		sum += p.getFitness();

	for (auto& p : m_population)
		p.getProbability() = p.getFitness() / sum;


	auto newPopulation = m_population;

	for (size_t i=1; i<m_population.size(); i++)
	{
		auto parent = m_population[improvedPoolSelection()];
		newPopulation[i].inherit(parent);

		newPopulation[i].reset();
		newPopulation[i].mutate();
	}
	
	m_population = newPopulation;

	m_population[0].reset();
	m_population[0].setColor(sf::Color::Green);


	m_txtGenInfo.setString("Generation: " + std::to_string(++m_generation));
}

int Population::poolSelection()
{
	for (int i = 0; i < 1000; i++)
	{
		int r1 = static_cast<int>(randNum(0, m_population.size() - 1));
		int r2 = static_cast<int>(randNum(0, m_population[0].getFitness()));

		bool p = m_population[r1].getFitness() > r2;
		if (m_population[r1].getFitness() > r2)
			return r1;
	}

	return 0;
}

int Population::improvedPoolSelection()
{
	int index = 0;
	float r = randNum(0, 1);

	while (r > 0)
	{
		r -= m_population[index].getProbability();
		index++;
	}

	return --index;
}
