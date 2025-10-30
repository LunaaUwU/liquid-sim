#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "block.h"
#include "material-type.h"

class Game;

class Grid
{
public:

	void init(sf::VideoMode videoMode);

	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window) const;


	void inputEvent(const sf::Event& event);

	void spawnBlock(Block* block);

	static constexpr float CELL_SIZE = 10.f;

private:

	void move(int i, int j);

	bool isInsideGrid(int i, int j) const;

	void changeMat(int value);

	void placeBlock();

	void removeBlock();

	sf::Vector2i m_mousePos;

	float m_moveTimer = 0.f;

	int m_rows;
	int m_columns;

	std::vector<std::vector<Block*>> m_grid;

	std::vector<Block*> m_activeGrid;

	std::vector<MaterialType> m_materialList;
	MaterialType m_selectedMaterial;
	int m_selectedMaterialIndex;

	bool m_leftMouseHeld = false;
	bool m_rightMouseHeld = false;
};