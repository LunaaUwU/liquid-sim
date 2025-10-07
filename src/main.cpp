#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Minesweeper"};
    window.setFramerateLimit(144);
    sf::Clock deltaClock;
    sf::Time elapsed;

    Game* game = new Game();

    game->init();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        elapsed = deltaClock.restart();

        if (window.hasFocus())
        {
            game->update(elapsed.asMilliseconds());
            game->render(window);
        }
    }

    return 0;
}