#include "game.h"

std::random_device Game::rd;
std::mt19937 Game::gen(Game::rd());

sf::RectangleShape Game::m_selectedMatShape;

void Game::init(sf::VideoMode videoMode)
{
    m_selectedMatShape.setSize(sf::Vector2f(30.f, 30.f));
    m_selectedMatShape.setPosition(sf::Vector2f(20.f, videoMode.height - 20.f - 30.f));
    m_selectedMatShape.setFillColor(sf::Color(0, 0, 0, 0));
    grid->init(videoMode);
}

void Game::update(const sf::Int32 deltaMS)
{
    grid->update(deltaMS);
}

void Game::render(sf::RenderWindow& window) const
{
    window.clear();

    grid->render(window);

	window.draw(m_selectedMatShape);

    window.display();
}

void Game::inputEvent(const sf::Event& event)
{
    grid->inputEvent(event);
}

void Game::restart()
{
    
}

int Game::randomInt(int min, int max)
{
    if (min > max)
    {
        std::swap(min, max);
    }

    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void Game::changeSelectedMat(MaterialType selectedMat)
{
	switch (selectedMat)
	{
		case MaterialType::Sand:
		{
			m_selectedMatShape.setFillColor(sf::Color(255, 255, 0));
			break;
		}
		case MaterialType::Water:
		{
			m_selectedMatShape.setFillColor(sf::Color(0, 0, 255));
			break;
		}
		case MaterialType::Stone:
		{
			m_selectedMatShape.setFillColor(sf::Color(135, 135, 135));
			break;
		}
		case MaterialType::Metal:
		{
			m_selectedMatShape.setFillColor(sf::Color(55, 55, 55));
			break;
		}
		case MaterialType::Steam:
		{
			m_selectedMatShape.setFillColor(sf::Color(215, 215, 215));
			break;
		}
		case MaterialType::Ground:
		{
			m_selectedMatShape.setFillColor(sf::Color(73, 29, 0));
			break;
		}
		default:
		{
			m_selectedMatShape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
}
