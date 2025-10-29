#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "material-type.h"

class UI
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;


	static void changeSelectedMat(MaterialType selectedMat);

private:

	static sf::RectangleShape m_selectedMatShape;
};