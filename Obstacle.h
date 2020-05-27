#pragma once

#include<SFML/Graphics.hpp>

class Obstacle
{
public:
	Obstacle(const sf::Vector2f size, const sf::Vector2f pos);

	void render(sf::RenderTarget& target);
	sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }

private:
	sf::RectangleShape m_shape;
};

