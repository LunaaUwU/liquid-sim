#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window = sf::RenderWindow{ { videoMode.width, videoMode.height }, "Liquid Simulator", sf::Style::Fullscreen};
    window.setFramerateLimit(144);
    sf::Clock deltaClock;
    sf::Time elapsed;

    Game* game = new Game();

    game->init(videoMode);

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            game->update(elapsed.asMilliseconds());
            game->render(window);
        }
    }

    return 0;
}