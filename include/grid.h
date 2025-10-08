#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "block.h"
#include "material-type.h"

class Grid
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;

private:

	void move(int i, int j);

	int m_rows;
	int m_columns;

	std::vector<std::vector<Block*>> m_grid;

};