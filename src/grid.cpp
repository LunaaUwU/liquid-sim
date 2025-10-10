#include <iostream>

#include "grid.h"
#include "game.h"

void Grid::init(sf::VideoMode videoMode)
{
	m_columns = videoMode.width / CELL_SIZE;
	m_rows = videoMode.height / CELL_SIZE;
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
			else if (posY == 0 || posX == 0 || posX == videoMode.width - CELL_SIZE)
			{
				type = MaterialType::Metal;
			}
			else
			{
				type = MaterialType::None;
			}
			m_grid[i][j]->init(type, posX, posY, i, j);
			if (m_grid[i][j]->getMatType() != MaterialType::None)
			{
				m_activeGrid.push_back(m_grid[i][j]);
			}
			posX += CELL_SIZE;
		}
		posY += CELL_SIZE;
		posX = 0.f;
	}
}

void Grid::update(const sf::Int32 deltaMS)
{
	// INPUT
	m_mousePos = sf::Mouse::getPosition();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE]->getMatType() == MaterialType::None)
		{
			m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE]->setMatType(MaterialType::Sand);
			m_activeGrid.push_back(m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE]);
		}
	}

	// MOVEMENT
	m_moveTimer += deltaMS;
	if (m_moveTimer >= Game::MOVE_INTERVAL)
	{
		// sorting
		std::sort(m_activeGrid.begin(), m_activeGrid.end(),
			[](Block* a, Block* b)
			{
				return a->getPos().y > b->getPos().y; // bottom to top
			});
		m_moveTimer = 0;
		for (int i = m_activeGrid.size() - 1; i >= 0; i--)
		{
			move(m_activeGrid[i]->getGridI(), m_activeGrid[i]->getGridJ());
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
		case MaterialType::Sand:
		{
			if (m_grid[i + 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::None);
				m_grid[i + 1][j]->setMatType(oldMat);
				auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
				if (it != m_activeGrid.end())
				{
					m_activeGrid.erase(it);
				}
				m_activeGrid.push_back(m_grid[i + 1][j]);
			}
			else
			{
				if (Game::randomInt(0, 1) == 0)
				{
					if (m_grid[i + 1][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i + 1][j - 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i + 1][j - 1]);
					}
					else if(m_grid[i + 1][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i + 1][j + 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i + 1][j + 1]);
					}
				}
				else
				{
					if (m_grid[i + 1][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i + 1][j + 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i + 1][j + 1]);
					}
					else if (m_grid[i + 1][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i + 1][j - 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i + 1][j - 1]);
					}
				}
			}
			break;
		}
	}
}