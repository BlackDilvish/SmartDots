#include "App.h"

App::App(const std::pair<size_t, size_t>& windowSize)
{
	std::srand(static_cast<size_t>(std::time(nullptr)));

	initWindow(windowSize);
}

void App::update()
{
	pollevents();
	updateClick();

	switch (m_currentState)
	{
	case States::SetupTarget:
		setupTarget();
		break;
	case States::SetupDots:
		setupDots();
		break;
	case States::Edit:
		moveObstacle();
		break;
	case States::Run:
		if(validClick())
			placeObstacle();

		m_testPopulation->update(m_window->getSize(), m_obstacles);
		break;
	default:
		break;
	}		
}

void App::render()
{
	m_window->clear(sf::Color::Black);

	for (auto& obstacle : m_obstacles)
		obstacle.render(*m_window);

	if(m_currentState == States::Run)
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

void App::updateClick()
{
	float dt = m_clock.restart().asSeconds();

	if (m_clickTimer < m_clickCooldown)
		m_clickTimer += dt;
}

void App::setupTarget()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
	Dot::getTarget().setPosition(sf::Vector2f(mousePos));

	if (validClick())
	{
		m_currentState = States::SetupDots;
		m_clickTimer = 0;
	}
}

void App::setupDots()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

	if (validClick())
	{
		Dot::getStartingPos() = sf::Vector2f(mousePos);
		m_testPopulation = std::make_unique<Population>(POPULATION_SIZE);
		m_currentState = States::Run;
		m_clickTimer = 0;
	}
}

void App::placeObstacle()
{
	sf::Vector2i firstPos = sf::Mouse::getPosition(*m_window);
	Obstacle obstacle(sf::Vector2f(100.f, 20.f), sf::Vector2f(firstPos));

	m_obstacles.push_back(obstacle);
	m_currentState = States::Edit;
	m_clickTimer = 0;
}

void App::moveObstacle()
{
	auto newSize = sf::Vector2f(sf::Mouse::getPosition(*m_window)) - m_obstacles[m_obstacles.size() - 1].getPosition();
	m_obstacles[m_obstacles.size() - 1].setSize(newSize);

	if (validClick())
	{
		m_currentState = States::Run;
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
