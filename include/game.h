#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "grid.h"
#include "material-type.h"

#include <random>


class Game
{
public:

    void init(sf::VideoMode videoMode);

    void update(sf::Int32 deltaMS);

    void render(sf::RenderWindow& window) const;

    void inputEvent(const sf::Event& event);

    void restart();


    static constexpr float MOVE_INTERVAL = 25.f;

    static int randomInt(int min, int max);

    static void changeSelectedMat(MaterialType selectedMat);

private:

    Grid* grid = new Grid();

    static sf::RectangleShape m_selectedMatShape;

    static std::random_device rd;
    static std::mt19937 gen;

};
