#include <iostream>

#include "grid.h"
#include "game.h"

void Grid::init(sf::VideoMode videoMode)
{
	m_columns = videoMode.width / 10;
	m_rows = videoMode.height / 10;
	MaterialType type;
	m_grid.resize(m_rows, std::vector<Block*>(m_columns, nullptr));
	float posX = 0;
	float posY = 0;
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_columns; ++j) {
			m_grid[i][j] = new Block(); // Create a block for each position
			if (posY >= videoMode.height - 60)
			{
				type = MaterialType::Ground;
			}
			else if (posY == 0 || posX == 0 || posX == videoMode.width - 10)
			{
				type = MaterialType::Metal;
			}
			else if (posY <= 30)
			{
				type = MaterialType::Water;
			}
			else
			{
				type = MaterialType::None;
			}
			m_grid[i][j]->init(type, posX, posY);
			posX += 10.f;
		}
		posY += 10.f;
		posX = 0.f;
	}
}

void Grid::update(const sf::Int32 deltaMS)
{
	m_moveTimer += deltaMS;
	if (m_moveTimer >= Game::MOVE_INTERVAL)
	{
		m_moveTimer = 0;
		for (int i = m_rows - 1; i >= 0; --i) {
			for (int j = m_columns - 1; j >= 0; --j) {
				move(i, j);
			}
		}
	}
}

void Grid::render(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_columns; ++j) {
			m_grid[i][j]->render(window);
		}
	}
}

void Grid::move(int i, int j)
{
	MaterialType oldMat = m_grid[i][j]->getMatType();
	switch (oldMat)
	{
		case MaterialType::Water:
		{
			if (i < m_rows)
			{
				if (m_grid[i + 1][j]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i + 1][j]->setMatType(oldMat);
				}
			}
			break;
		}
	}
}