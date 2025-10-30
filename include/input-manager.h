#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class InputManager
{
public:

	static bool LEFT_MOUSE_HELD;

	static bool RIGHT_MOUSE_HELD;


	void processEvent(const sf::Event& event);

private:

};