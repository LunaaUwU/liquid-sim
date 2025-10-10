#include "game.h"

std::random_device Game::rd;
std::mt19937 Game::gen(Game::rd());

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