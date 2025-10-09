#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "grid.h"

#include <random>


class Game
{
public:

    void init(sf::VideoMode videoMode);

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void restart();


    static constexpr float MOVE_INTERVAL = 0.f;

    static int randomInt(int min, int max);

private:

    Grid* grid = new Grid();

    

    static std::random_device rd;
    static std::mt19937 gen;

};
