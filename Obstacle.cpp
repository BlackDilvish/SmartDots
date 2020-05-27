#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f size, const sf::Vector2f pos)
{
	m_shape.setSize(size);
	m_shape.setPosition(pos);
	m_shape.setFillColor(sf::Color::Blue);
}

void Obstacle::render(sf::RenderTarget& target)
{
	target.draw(m_shape);
}
