#include "game.h"


void Game::update(const sf::Int32 deltaMS)
{

}

void Game::render(sf::RenderWindow& window) const
{
    window.clear();

    window.display();
}

void Game::init(sf::VideoMode videoMode)
{

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