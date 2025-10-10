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

	int numMaterials = static_cast<int>(MaterialType::Count);
	MaterialType material;
	for (int i = 0; i < numMaterials; i++)
	{
		material = static_cast<MaterialType>(i);
		if (material != MaterialType::Ground && material != MaterialType::Count)
		{
			m_materialList.push_back(material);
		}
	}
	m_selectedMaterialIndex = 0;
	m_selectedMaterial = m_materialList[m_selectedMaterialIndex];
}

void Grid::update(const sf::Int32 deltaMS)
{
	if (m_leftMouseHeld)
	{
		m_mousePos = sf::Mouse::getPosition();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Block* block = m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE];
			if (m_selectedMaterial == MaterialType::None)
			{
				if (block->getMatType() != MaterialType::None)
				{
					block->setMatType(m_selectedMaterial);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), block);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
				}
			}
			else
			{
				if (block->getMatType() == MaterialType::None)
				{
					block->setMatType(m_selectedMaterial);
					m_activeGrid.push_back(block);
				}
			}
		}
	}
	m_moveTimer += deltaMS;
	if (m_moveTimer >= Game::MOVE_INTERVAL)
	{
		m_moveTimer = 0;
		// sorting
		std::sort(m_activeGrid.begin(), m_activeGrid.end(),
			[](Block* a, Block* b)
			{
				return a->getPos().y < b->getPos().y; // bottom to top
			});
		// movint
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

void Grid::inputEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			if (event.mouseWheelScroll.delta < 0)
			{
				m_selectedMaterialIndex++;
				if (m_selectedMaterialIndex >= m_materialList.size())
				{
					m_selectedMaterialIndex = 0;
				}
			}
			else if (event.mouseWheelScroll.delta > 0)
			{
				m_selectedMaterialIndex--;
				if (m_selectedMaterialIndex < 0)
				{
					m_selectedMaterialIndex = m_materialList.size() - 1;
				}
			}
			m_selectedMaterial = m_materialList[m_selectedMaterialIndex];
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_leftMouseHeld = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			m_leftMouseHeld = false;
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
		case MaterialType::Stone:
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
			break;
		}
		case MaterialType::Water:
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
				if (m_grid[i][j]->getWaterMoveDir() == 0)
				{
					if (Game::randomInt(0, 1) == 0)
					{
						m_grid[i][j]->setWaterMoveDir(1);
					}
					else
					{
						m_grid[i][j]->setWaterMoveDir(2);
					}
				}

				if (m_grid[i][j]->getWaterMoveDir() == 1)
				{
					if (m_grid[i][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i][j - 1]->setMatType(oldMat);
						m_grid[i][j]->setWaterMoveDir(0);
						m_grid[i][j - 1]->setWaterMoveDir(1);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i][j - 1]);
					}
					else if (m_grid[i][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i][j + 1]->setMatType(oldMat);
						m_grid[i][j]->setWaterMoveDir(0);
						m_grid[i][j + 1]->setWaterMoveDir(2);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i][j + 1]);
					}
				}
				else if(m_grid[i][j]->getWaterMoveDir() == 2)
				{
					if (m_grid[i][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i][j + 1]->setMatType(oldMat);
						m_grid[i][j]->setWaterMoveDir(0);
						m_grid[i][j + 1]->setWaterMoveDir(2);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i][j + 1]);
					}
					else if (m_grid[i][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i][j - 1]->setMatType(oldMat);
						m_grid[i][j]->setWaterMoveDir(0);
						m_grid[i][j - 1]->setWaterMoveDir(1);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i][j - 1]);
					}
				}
			}
			break;
		}
		case MaterialType::Steam:
		{
			if (m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::None);
				m_grid[i - 1][j]->setMatType(oldMat);
				auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
				if (it != m_activeGrid.end())
				{
					m_activeGrid.erase(it);
				}
				m_activeGrid.push_back(m_grid[i - 1][j]);
			}
			else
			{
				if (Game::randomInt(0, 1) == 0)
				{
					if (m_grid[i - 1][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i - 1][j - 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i - 1][j - 1]);
					}
					else if (m_grid[i - 1][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i - 1][j + 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i - 1][j + 1]);
					}
				}
				else
				{
					if (m_grid[i - 1][j + 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i - 1][j + 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i - 1][j + 1]);
					}
					else if (m_grid[i - 1][j - 1]->getMatType() == MaterialType::None)
					{
						m_grid[i][j]->setMatType(MaterialType::None);
						m_grid[i - 1][j - 1]->setMatType(oldMat);
						auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
						if (it != m_activeGrid.end())
						{
							m_activeGrid.erase(it);
						}
						m_activeGrid.push_back(m_grid[i - 1][j - 1]);
					}
				}
			}
			break;
		}
	}
}