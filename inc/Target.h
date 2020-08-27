#pragma once

#include<SFML/Graphics.hpp>

class Target
{
public:
	Target();
	Target(const sf::Vector2f& pos);

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(const sf::Vector2f& pos);

	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape m_shape;
	const sf::Vector2f size{ 10.f, 10.f };
};

