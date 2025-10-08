#include "game.h"

void Game::init(sf::VideoMode videoMode)
{
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

    window.display();
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