#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "grid.h"
#include "ui.h"
#include "input-manager.h"

#include <random>


class Game
{
public:

    void init(const sf::VideoMode videoMode) const;

    void update(sf::Int32 deltaMS) const;

    void render(sf::RenderWindow& window) const;

    static void inputEvent(const sf::Event& event) const;

    void restart() const;


    static constexpr float MOVE_INTERVAL = 5.f;

    static int randomInt(int min, int max);

private:

    Grid* m_grid = new Grid();

    UI* m_ui = new UI();

    InputManager* m_inputManager = new InputManager();

    static std::random_device rd;
    static std::mt19937 gen;

};
