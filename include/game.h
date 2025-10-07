#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <random>


class Game
{
public:

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void init();

    void restart();

private:

    int randomInt(int min, int max);

    sf::RectangleShape m_coso;

    std::random_device rd;

};
