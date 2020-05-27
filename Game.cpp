#include "Game.h"

Game::Game(const std::pair<size_t, size_t>& windowSize)
{
	std::srand(std::time(nullptr));

	initWindow(windowSize);

	m_obstacles.push_back(Obstacle({ 200.f, 50.f }, { 400.f, 300.f }));
	m_obstacles.push_back(Obstacle({ 100.f, 20.f }, { 400.f, 100.f }));
}

void Game::update()
{
	pollevents();

	m_testPopulation->update(m_window->getSize(), m_obstacles);
}

void Game::render()
{
	m_window->clear(sf::Color::Black);

	for (auto& obstacle : m_obstacles)
		obstacle.render(*m_window);

	m_testPopulation->render(*m_window);

	Dot::getTarget().render(*m_window);

	m_window->display();
}

bool Game::isActive() const
{
	return m_window->isOpen();
}

void Game::initWindow(const std::pair<size_t, size_t>& windowSize)
{
	sf::VideoMode videomode(windowSize.first, windowSize.second);

	m_window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videomode, "Learning dots"));
	m_window->setFramerateLimit(600);
}

void Game::pollevents()
{
	sf::Event event;

	while (m_window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			m_window->close();
}
