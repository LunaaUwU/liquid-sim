#include "input-manager.h"

bool InputManager::LEFT_MOUSE_HELD = false;
bool InputManager::RIGHT_MOUSE_HELD = false;

void InputManager::processEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			LEFT_MOUSE_HELD = true;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			RIGHT_MOUSE_HELD = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			LEFT_MOUSE_HELD = false;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			RIGHT_MOUSE_HELD = false;
		}
	}
}
