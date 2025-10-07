#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{
    
}

void Game::render(sf::RenderWindow& window) const
{
    window.clear();

    window.draw(m_coso);

    window.display();
}

void Game::init()
{
    m_coso.setSize(sf::Vector2f(50.f, 50.f));
    m_coso.setFillColor(sf::Color(0, 0, 255));
    m_coso.setPosition(100.f, 100.f);
}

void Game::restart()
{
    
}

int Game::randomInt(int min, int max)
{
    if (min > max)
    {
        int old = min;
        min = max;
        max = old;
    }
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}