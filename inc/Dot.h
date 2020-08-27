#pragma once

#include<SFML/Graphics.hpp>
#include"Brain.h"
#include"Target.h"
#include"Obstacle.h"

size_t constexpr BRAIN_SIZE = 1000;

class Dot
{
public:
	Dot();

	void update(const sf::Vector2u& windowSize, const std::vector<Obstacle>& obstacles);
	void render(sf::RenderTarget& target);

	void kill() { m_isAlive = false; }
	void mutate() { m_brain.mutate(); }
	void calculateFitness();
	void reset();
	void inherit(const Dot& parent);

	static sf::Vector2f& getStartingPos() { return Dot::startingPos; }
	static Target& getTarget() { return Dot::target; }
	size_t getStep() const { return m_brain.step; }
	float getFitness() const { return m_fitness; }
	float& getProbability() { return m_probability; }
	bool active() const { return m_isAlive && !m_finished; }
	bool finished() const { return m_finished; }

	void setColor(const sf::Color color) { m_shape.setFillColor(color); }
		
private:

	void move();

	bool hitsWindow(const sf::Vector2u& windowSize) const;
	bool hitsObstacles(const std::vector<Obstacle>& obstacles) const;
	bool reachesTarget() const;

	bool m_isAlive = true;
	bool m_finished = false;
	float m_fitness = 0;
	float m_probability = 0;
	
	sf::CircleShape m_shape;
	Brain m_brain{ BRAIN_SIZE };

	static const float size;
	static const float speed;
	static sf::Vector2f startingPos;
	static Target target;
};

