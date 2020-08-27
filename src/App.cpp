#include "App.h"

App::App(const std::pair<size_t, size_t>& windowSize)
{
	std::srand(static_cast<size_t>(std::time(nullptr)));

	initWindow(windowSize);
}

void App::update()
{
	pollevents();
	handleClick();

	if(!m_editing)
		m_testPopulation->update(m_window->getSize(), m_obstacles);
}

void App::render()
{
	m_window->clear(sf::Color::Black);

	for (auto& obstacle : m_obstacles)
		obstacle.render(*m_window);

	m_testPopulation->render(*m_window);
	Dot::getTarget().render(*m_window);

	m_window->display();
}

bool App::isActive() const
{
	return m_window->isOpen();
}

void App::initWindow(const std::pair<size_t, size_t>& windowSize)
{
	sf::VideoMode videomode(windowSize.first, windowSize.second);

	m_window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videomode, "Genetically intelligent dots"));
}

void App::pollevents()
{
	sf::Event event;

	while (m_window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			m_window->close();
}

void App::handleClick()
{
	float dt = m_clock.restart().asSeconds();

	if (m_clickTimer < m_clickCooldown)
		m_clickTimer += dt;

	if (validClick() && !m_editing)
	{
		placeObstacle();
		m_clickTimer = 0;
	}

	if (m_editing)
		moveObstacle();
}

void App::placeObstacle()
{
	auto firstPos = sf::Mouse::getPosition(*m_window);
	Obstacle obstacle(sf::Vector2f(100.f, 20.f), sf::Vector2f(firstPos));

	m_obstacles.push_back(obstacle);
	m_editing = true;
}

void App::moveObstacle()
{
	auto newSize = sf::Vector2f(sf::Mouse::getPosition(*m_window)) - m_obstacles[m_obstacles.size() - 1].getPosition();
	m_obstacles[m_obstacles.size() - 1].setSize(newSize);

	if (validClick())
	{
		m_editing = false;
		m_clickTimer = 0;
	}
}

bool App::validClick() const
{
	auto mousePos = sf::Mouse::getPosition(*m_window);

	bool inWindow = mousePos.x > 0 && mousePos.x < static_cast<int>(m_window->getSize().x)
		&& mousePos.y > 0 && mousePos.y < static_cast<int>(m_window->getSize().y);

	bool validTime = m_clickTimer >= m_clickCooldown;

	return sf::Mouse::isButtonPressed(sf::Mouse::Left) && inWindow && validTime;
}
