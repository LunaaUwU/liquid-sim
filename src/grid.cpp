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
		if (material != MaterialType::Ground && material != MaterialType::Count && material != MaterialType::None)
		{
			m_materialList.push_back(material);
		}
	}
	m_selectedMaterialIndex = 0;
	m_selectedMaterial = m_materialList[m_selectedMaterialIndex];
	UI::changeSelectedMat(m_selectedMaterial);
}

void Grid::update(const sf::Int32 deltaMS)
{
	if (InputManager::LEFT_MOUSE_HELD)
	{
		m_mousePos = sf::Mouse::getPosition();
		Block* block = m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE];

		if (block->getMatType() == MaterialType::None)
		{
			block->setMatType(m_selectedMaterial);
			m_activeGrid.push_back(block);
		}
	}
	if (InputManager::RIGHT_MOUSE_HELD)
	{
		m_mousePos = sf::Mouse::getPosition();
		Block* block = m_grid[m_mousePos.y / CELL_SIZE][m_mousePos.x / CELL_SIZE];
		if (block->getMatType() != MaterialType::None)
		{
			block->setMatType(MaterialType::None);
			block->setIsSpawner(false);
			auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), block);
			if (it != m_activeGrid.end())
			{
				m_activeGrid.erase(it);
			}
		}
		/*if (m_selectedMaterial == MaterialType::None)
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
				block->setIsSpawner(true);
				m_activeGrid.push_back(block);
			}
		}*/
	}
	m_moveTimer += deltaMS;
	std::sort(m_activeGrid.begin(), m_activeGrid.end(),
		[](Block* a, Block* b)
		{
			return a->getPos().y < b->getPos().y; // bottom to top
		});
	for (int i = m_activeGrid.size() - 1; i >= 0; i--)
	{
		if (m_activeGrid[i]->getMatType() == MaterialType::Steam &&
			isInsideGrid(m_activeGrid[i]->getGridI() - 1, m_activeGrid[i]->getGridJ()) &&
			m_grid[m_activeGrid[i]->getGridI() - 1][m_activeGrid[i]->getGridJ()]->getMatType() != MaterialType::None &&
			isInsideGrid(m_activeGrid[i]->getGridI(), m_activeGrid[i]->getGridJ() - 1) &&
			m_grid[m_activeGrid[i]->getGridI()][m_activeGrid[i]->getGridJ() - 1]->getMatType() != MaterialType::None &&
			isInsideGrid(m_activeGrid[i]->getGridI() + 1, m_activeGrid[i]->getGridJ()) &&
			m_grid[m_activeGrid[i]->getGridI() + 1][m_activeGrid[i]->getGridJ()]->getMatType() != MaterialType::None &&
			isInsideGrid(m_activeGrid[i]->getGridI(), m_activeGrid[i]->getGridJ() + 1) &&
			m_grid[m_activeGrid[i]->getGridI()][m_activeGrid[i]->getGridJ() + 1]->getMatType() != MaterialType::None)
		{
			m_activeGrid[i]->setCondensationTimer(m_activeGrid[i]->getCondensationTimer() + deltaMS);
		}
		else
		{
			m_activeGrid[i]->setCondensationTimer(0);
		}
	}
	if (m_moveTimer >= Game::MOVE_INTERVAL)
	{
		m_moveTimer = 0;
		// sorting
		std::sort(m_activeGrid.begin(), m_activeGrid.end(),
			[](Block* a, Block* b)
			{
				return a->getPos().y < b->getPos().y; // bottom to top
			});
		for (int i = m_activeGrid.size() - 1; i >= 0; i--)
		{
			if (!m_activeGrid[i]->getIsSpawner())
				move(m_activeGrid[i]->getGridI(), m_activeGrid[i]->getGridJ());
			else
			{
				int spawnI = m_activeGrid[i]->getGridI() + 1;
				int spawnJ = m_activeGrid[i]->getGridJ();
				if (isInsideGrid(spawnI, spawnJ) && m_grid[spawnI][spawnJ]->getMatType() == MaterialType::None)
				{
					Block* target = m_grid[spawnI][spawnJ];
					target->setMatType(m_activeGrid[i]->getMatType());
					m_activeGrid.push_back(target);
				}
			}
		}
	}
}

void Grid::render(sf::RenderWindow& window) const
{
	for (int i = m_activeGrid.size() - 1; i >= 0; i--)
	{
		m_activeGrid[i]->render(window);
	}
}

void Grid::spawnBlock(Block* block)
{
	block->setMatType(m_selectedMaterial);
	block->setIsSpawner(true);
	m_activeGrid.push_back(block);
}

void Grid::move(int i, int j)
{
	MaterialType oldMat = m_grid[i][j]->getMatType();
	switch (oldMat)
	{
		case MaterialType::Sand:
		{
			if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::None)
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
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Water && isInsideGrid(i - 1, j) && m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::Water);
				m_grid[i + 1][j]->setMatType(MaterialType::Sand);
			}
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Lava && isInsideGrid(i - 1, j) && m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::Lava);
				m_grid[i + 1][j]->setMatType(MaterialType::Sand);
			}
			else
			{
				if (Game::randomInt(0, 1) == 0)
				{
					if (isInsideGrid(i + 1, j - 1) && m_grid[i + 1][j - 1]->getMatType() == MaterialType::None && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None)
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
					else if (isInsideGrid(i + 1, j - 1) && m_grid[i + 1][j - 1]->getMatType() == MaterialType::Water)
					{
						m_grid[i][j]->setMatType(MaterialType::Water);
						m_grid[i + 1][j - 1]->setMatType(MaterialType::Sand);
					}
					else if (isInsideGrid(i + 1, j - 1) && m_grid[i + 1][j - 1]->getMatType() == MaterialType::Lava)
					{
						m_grid[i][j]->setMatType(MaterialType::Lava);
						m_grid[i + 1][j - 1]->setMatType(MaterialType::Sand);
					}
					else if(isInsideGrid(i + 1, j + 1) &&m_grid[i + 1][j + 1]->getMatType() == MaterialType::None && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None)
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
					else if (isInsideGrid(i + 1, j + 1) && m_grid[i + 1][j + 1]->getMatType() == MaterialType::Water)
					{
						m_grid[i][j]->setMatType(MaterialType::Water);
						m_grid[i + 1][j + 1]->setMatType(MaterialType::Sand);
					}
					else if (isInsideGrid(i + 1, j + 1) && m_grid[i + 1][j + 1]->getMatType() == MaterialType::Lava)
					{
						m_grid[i][j]->setMatType(MaterialType::Lava);
						m_grid[i + 1][j + 1]->setMatType(MaterialType::Sand);
					}
				}
				else
				{
					if (isInsideGrid(i + 1, j + 1) && m_grid[i + 1][j + 1]->getMatType() == MaterialType::None && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None)
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
					else if (isInsideGrid(i + 1, j - 1) && m_grid[i + 1][j - 1]->getMatType() == MaterialType::None && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None)
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
			if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::None)
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
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Water && isInsideGrid(i - 1, j) && m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::Water);
				m_grid[i + 1][j]->setMatType(MaterialType::Stone);
			}
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Lava && isInsideGrid(i - 1, j) && m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::Lava);
				m_grid[i + 1][j]->setMatType(MaterialType::Stone);
			}
			break;
		}
		case MaterialType::Water:
		{
			if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::None);
				m_grid[i + 1][j]->setMatType(oldMat);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i + 1][j]->setMoveDir(0);
				auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
				if (it != m_activeGrid.end())
				{
					m_activeGrid.erase(it);
				}
				m_activeGrid.push_back(m_grid[i + 1][j]);
			}
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Lava)
			{
				m_grid[i][j]->setMatType(MaterialType::Steam);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i + 1][j]->setMatType(MaterialType::Stone);
				m_grid[i + 1][j]->setMoveDir(0);
			}
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Steam)
			{
				m_grid[i][j]->setMatType(MaterialType::Steam);
				m_grid[i + 1][j]->setMatType(MaterialType::Water);
			}
			else
			{
				if (m_grid[i][j]->getMoveDir() == 0)
				{
					int leftDropDist = INT_MAX;
					int rightDropDist = INT_MAX;

					// check left direction for a drop
					for (int k = j - 1; k >= 0; k--)
					{
						if (!isInsideGrid(i, k)) break;
						// find the first spot where water could fall down
						if (isInsideGrid(i + 1, k) && m_grid[i + 1][k]->getMatType() == MaterialType::None)
						{
							leftDropDist = j - k;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// check right direction for a drop
					for (int k = j + 1; k < m_columns; k++)
					{
						if (!isInsideGrid(i, k)) break;
						if (isInsideGrid(i + 1, k) && m_grid[i + 1][k]->getMatType() == MaterialType::None)
						{
							rightDropDist = k - j;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// move toward the nearest drop
					if (leftDropDist < rightDropDist && leftDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(1); // left
					}
					else if (rightDropDist < leftDropDist && rightDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(2); // right
					}
					else
					{
						// random
						bool canMoveLeft = isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None;
						bool canMoveRight = isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None;

						if (canMoveLeft && canMoveRight)
							m_grid[i][j]->setMoveDir(Game::randomInt(1, 2));
						else if (canMoveLeft)
							m_grid[i][j]->setMoveDir(1);
						else if (canMoveRight)
							m_grid[i][j]->setMoveDir(2);
					}
				}
				if (m_grid[i][j]->getMoveDir() == 1 && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j - 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j - 1]->setMoveDir(1);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j - 1]);
				}
				else if (m_grid[i][j]->getMoveDir() == 1 && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::Lava)
				{
					m_grid[i][j]->setMatType(MaterialType::Steam);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j - 1]->setMatType(MaterialType::Stone);
					m_grid[i][j - 1]->setMoveDir(0);
				}
				else
				{
					m_grid[i][j]->setMoveDir(2);
				}
				if (m_grid[i][j]->getMoveDir() == 2 && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j + 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j + 1]->setMoveDir(2);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j + 1]);
				}
				else if (m_grid[i][j]->getMoveDir() == 2 && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::Lava)
				{
					m_grid[i][j]->setMatType(MaterialType::Steam);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j + 1]->setMatType(MaterialType::Stone);
					m_grid[i][j + 1]->setMoveDir(0);
				}
				else
				{
					m_grid[i][j]->setMoveDir(1);
				}
			}
			break;
		}
		case MaterialType::Steam:
		{
			if (m_grid[i][j]->getCondensationTimer() >= Block::CONDENSATION_THRESHOLD)
			{
				m_grid[i][j]->setMatType(MaterialType::Water);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i][j]->setCondensationTimer(0);
			}
			if (isInsideGrid(i - 1, j) && m_grid[i - 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::None);
				m_grid[i - 1][j]->setMatType(oldMat);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i - 1][j]->setMoveDir(0);
				auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
				if (it != m_activeGrid.end())
				{
					m_activeGrid.erase(it);
				}
				m_activeGrid.push_back(m_grid[i - 1][j]);
			}
			else
			{
				if (m_grid[i][j]->getMoveDir() == 0)
				{
					int leftDropDist = INT_MAX;
					int rightDropDist = INT_MAX;

					// check left direction for a drop
					for (int k = j - 1; k >= 0; k--)
					{
						if (!isInsideGrid(i, k)) break;
						// find the first spot where water could fall down
						if (isInsideGrid(i - 1, k) && m_grid[i - 1][k]->getMatType() == MaterialType::None)
						{
							leftDropDist = j - k;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// check right direction for a drop
					for (int k = j + 1; k < m_columns; k++)
					{
						if (!isInsideGrid(i, k)) break;
						if (isInsideGrid(i - 1, k) && m_grid[i - 1][k]->getMatType() == MaterialType::None)
						{
							rightDropDist = k - j;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// move toward the nearest drop
					if (leftDropDist < rightDropDist && leftDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(1); // left
					}
					else if (rightDropDist < leftDropDist && rightDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(2); // right
					}
					else
					{
						// random
						bool canMoveLeft = isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None;
						bool canMoveRight = isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None;

						if (canMoveLeft && canMoveRight)
							m_grid[i][j]->setMoveDir(Game::randomInt(1, 2));
						else if (canMoveLeft)
							m_grid[i][j]->setMoveDir(1);
						else if (canMoveRight)
							m_grid[i][j]->setMoveDir(2);
					}
				}
				if (m_grid[i][j]->getMoveDir() == 1 && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j - 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j - 1]->setMoveDir(1);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j - 1]);
				}
				else
				{
					m_grid[i][j]->setMoveDir(2);
				}
				if (m_grid[i][j]->getMoveDir() == 2 && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j + 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j + 1]->setMoveDir(2);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j + 1]);
				}
				else
				{
					m_grid[i][j]->setMoveDir(1);
				}
			}
			break;
		}
		case MaterialType::Lava:
		{
			if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::None)
			{
				m_grid[i][j]->setMatType(MaterialType::None);
				m_grid[i + 1][j]->setMatType(oldMat);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i + 1][j]->setMoveDir(0);
				auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
				if (it != m_activeGrid.end())
				{
					m_activeGrid.erase(it);
				}
				m_activeGrid.push_back(m_grid[i + 1][j]);
			}
			else if (isInsideGrid(i + 1, j) && m_grid[i + 1][j]->getMatType() == MaterialType::Water)
			{
				m_grid[i][j]->setMatType(MaterialType::Steam);
				m_grid[i][j]->setMoveDir(0);
				m_grid[i + 1][j]->setMatType(MaterialType::Stone);
				m_grid[i + 1][j]->setMoveDir(0);
			}
			else
			{
				if (m_grid[i][j]->getMoveDir() == 0)
				{
					int leftDropDist = INT_MAX;
					int rightDropDist = INT_MAX;

					// check left direction for a drop
					for (int k = j - 1; k >= 0; k--)
					{
						if (!isInsideGrid(i, k)) break;
						// find the first spot where water could fall down
						if (isInsideGrid(i + 1, k) && m_grid[i + 1][k]->getMatType() == MaterialType::None)
						{
							leftDropDist = j - k;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// check right direction for a drop
					for (int k = j + 1; k < m_columns; k++)
					{
						if (!isInsideGrid(i, k)) break;
						if (isInsideGrid(i + 1, k) && m_grid[i + 1][k]->getMatType() == MaterialType::None)
						{
							rightDropDist = k - j;
							break;
						}
						// stop if it hits a wall
						if (m_grid[i][k]->getMatType() != MaterialType::None)
							break;
					}

					// move toward the nearest drop
					if (leftDropDist < rightDropDist && leftDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(1); // left
					}
					else if (rightDropDist < leftDropDist && rightDropDist != INT_MAX)
					{
						m_grid[i][j]->setMoveDir(2); // right
					}
					else
					{
						// random
						bool canMoveLeft = isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None;
						bool canMoveRight = isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None;

						if (canMoveLeft && canMoveRight)
							m_grid[i][j]->setMoveDir(Game::randomInt(1, 2));
						else if (canMoveLeft)
							m_grid[i][j]->setMoveDir(1);
						else if (canMoveRight)
							m_grid[i][j]->setMoveDir(2);
					}
				}
				if (m_grid[i][j]->getMoveDir() == 1 && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j - 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j - 1]->setMoveDir(1);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j - 1]);
				}
				else if (m_grid[i][j]->getMoveDir() == 1 && isInsideGrid(i, j - 1) && m_grid[i][j - 1]->getMatType() == MaterialType::Water)
				{
					m_grid[i][j]->setMatType(MaterialType::Steam);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j - 1]->setMatType(MaterialType::Stone);
					m_grid[i][j - 1]->setMoveDir(0);
				}
				else
				{
					m_grid[i][j]->setMoveDir(2);
				}
				if (m_grid[i][j]->getMoveDir() == 2 && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::None)
				{
					m_grid[i][j]->setMatType(MaterialType::None);
					m_grid[i][j + 1]->setMatType(oldMat);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j + 1]->setMoveDir(2);
					auto it = std::find(m_activeGrid.begin(), m_activeGrid.end(), m_grid[i][j]);
					if (it != m_activeGrid.end())
					{
						m_activeGrid.erase(it);
					}
					m_activeGrid.push_back(m_grid[i][j + 1]);
				}
				else if (m_grid[i][j]->getMoveDir() == 2 && isInsideGrid(i, j + 1) && m_grid[i][j + 1]->getMatType() == MaterialType::Water)
				{
					m_grid[i][j]->setMatType(MaterialType::Steam);
					m_grid[i][j]->setMoveDir(0);
					m_grid[i][j + 1]->setMatType(MaterialType::Stone);
					m_grid[i][j + 1]->setMoveDir(0);
				}
				else
				{
					m_grid[i][j]->setMoveDir(1);
				}
			}
			break;
		}
	}
}

bool Grid::isInsideGrid(int i, int j) const
{
	return i >= 0 && i < m_rows && j >= 0 && j < m_columns;
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
			UI::changeSelectedMat(m_selectedMaterial);
		}
	}
}