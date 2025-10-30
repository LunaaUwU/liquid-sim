#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"
#include "input-manager.h"

class UI
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;

	void cleanup();

	static void changeSelectedMat(MaterialType selectedMat);

private:

	static sf::RectangleShape m_selectedMatShape;
	static sf::Text m_selectedMatText;
	static sf::Font m_selectedMatFont;
};