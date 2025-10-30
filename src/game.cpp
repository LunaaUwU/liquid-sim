#include "game.h"

std::random_device Game::rd;
std::mt19937 Game::gen(Game::rd());

void Game::init(sf::VideoMode videoMode)
{
    m_ui->init(videoMode, m_grid);
    m_grid->init(videoMode);
}

void Game::update(const sf::Int32 deltaMS)
{
    m_grid->update(deltaMS);
}

void Game::render(sf::RenderWindow& window) const
{
    window.clear();

    m_grid->render(window);

	m_ui->render(window);

    window.display();
}

void Game::inputEvent(const sf::Event& event)
{
    m_inputManager->processEvent(event);
}

void Game::restart()
{
    
}

void Game::cleanup()
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