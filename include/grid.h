#pragma once
#include <SFML/Graphics.hpp>
#include "block.h"

class Game;

class Grid
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;


	void inputEvent(const sf::Event& event);

	void spawnBlock(Block* block);

	void clearBoard();

	static constexpr float CELL_SIZE = 10.f;

	bool getIsSpawner()
	{
		return m_isSpawner;
	}

	void setIsSpawner(bool isSpawner)
	{
		m_isSpawner = isSpawner;
	}


private:

	void move(int i, int j);

	bool isInsideGrid(int i, int j) const;

	void placeBlock();

	void removeBlock();

	sf::Vector2i m_mousePos;

	float m_moveTimer = 0.f;

	int m_rows;
	int m_columns;

	std::vector<std::vector<Block*>> m_grid;

	std::vector<Block*> m_activeGrid;

	bool m_leftMouseHeld = false;
	bool m_rightMouseHeld = false;

	bool m_isSpawner = false;
};