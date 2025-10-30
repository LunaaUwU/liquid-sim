#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window = sf::RenderWindow{ { videoMode.width, videoMode.height }, "Liquid Simulator", sf::Style::Fullscreen};
    window.setFramerateLimit(144);
    sf::Clock deltaClock;
    sf::Time elapsed;

    sf::Clock clock;
    float fps = 0.f;

    Game* game = new Game();

    game->init(videoMode);

    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        fps = 1.f / elapsed.asSeconds();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                game->cleanup();
                window.close();
            }

            game->inputEvent(event);
        }
        elapsed = deltaClock.restart();

        if (window.hasFocus())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                game->cleanup();
                window.close();
            }
            game->update(elapsed.asMilliseconds());
            game->render(window);
        }
    }

    return 0;
}