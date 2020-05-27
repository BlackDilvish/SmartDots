#include "Target.h"

Target::Target(const sf::Vector2f& pos)
{
	m_shape.setSize(Target::size);
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setOrigin(Target::size / 2.f);
	m_shape.setPosition(pos);
}

sf::Vector2f Target::getPosition() const
{
	return m_shape.getPosition();
}

sf::FloatRect Target::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

void Target::render(sf::RenderTarget& target)
{
	target.draw(m_shape);
}
