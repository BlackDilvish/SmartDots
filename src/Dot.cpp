#include "Dot.h"

Dot::Dot()
{
	m_shape.setRadius(Dot::size);
	m_shape.setOrigin(Dot::size, Dot::size);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setPosition(Dot::startingPos);
}

void Dot::update(const sf::Vector2u& windowSize, const std::vector<Obstacle>& obstacles)
{
	if (m_isAlive && !m_finished)
		move();
	
	if (hitsWindow(windowSize) || hitsObstacles(obstacles))
		m_isAlive = false;
	else if (reachesTarget())
		m_finished = true;
}

void Dot::render(sf::RenderTarget& target)
{
	if(m_isAlive)
		target.draw(m_shape);
}

void Dot::calculateFitness()
{
	if(m_finished)
		m_fitness = 1.f/16 + 10000.f / (m_brain.step * m_brain.step);
	else
	{
		auto distVec = m_shape.getPosition() - Dot::target.getPosition();
		auto dist = std::sqrt(std::pow(distVec.x, 2) + std::pow(distVec.y, 2));

		m_fitness = 1.f / dist;
	}

	m_fitness *= 1e3;
}

void Dot::reset()
{
	m_isAlive = true;
	m_finished = false;
	m_fitness = 0;
	m_brain.step = 0;

	m_shape.setPosition(Dot::startingPos);
}

void Dot::inherit(const Dot& parent)
{
	for (size_t i = 0; i < BRAIN_SIZE; i++)
		m_brain.directions[i] = parent.m_brain.directions[i];
}

void Dot::move()
{
	if (m_brain.step < BRAIN_SIZE)
	{
		m_shape.move(m_brain.directions[m_brain.step] * Dot::speed);
		m_brain.step++;
	}
	else
		m_isAlive = false;
}

bool Dot::hitsWindow(const sf::Vector2u& windowSize) const
{
	if (m_shape.getPosition().x < 0 || m_shape.getPosition().x > windowSize.x
		|| m_shape.getPosition().y < 0 || m_shape.getPosition().y > windowSize.y)
		return true;

	return false;
}

bool Dot::hitsObstacles(const std::vector<Obstacle>& obstacles) const
{
	bool hits = false;

	for (const auto& obstacle : obstacles)
		if (m_shape.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		{
			hits = true;
			break;
		}

	return hits;
}

bool Dot::reachesTarget() const
{
	return m_shape.getGlobalBounds().intersects(Dot::target.getGlobalBounds());
}

Target Dot::target{ sf::Vector2f(480.f, 10.f) };

const float Dot::speed = 10.f;

const float Dot::size = 5.f;

const sf::Vector2f Dot::startingPos = sf::Vector2f(400, 700);
