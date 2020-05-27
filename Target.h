#pragma once

#include<SFML/Graphics.hpp>

class Target
{
public:
	Target(const sf::Vector2f& pos);

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape m_shape;
	const sf::Vector2f size{ 10.f, 10.f };
};

