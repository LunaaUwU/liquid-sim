#include "block.h"
#include "grid.h"

void Block::init(MaterialType materialType, int posX, int posY, int i, int j)
{
	setMatType(materialType);
	m_shape.setSize(sf::Vector2f(Grid::CELL_SIZE, Grid::CELL_SIZE));
	m_shape.setPosition(posX, posY);
	gridI = i;
	gridJ = j;
}

void Block::render(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

void Block::setMatType(MaterialType type)
{
	m_materialType = type;
	switch (m_materialType)
	{
		case MaterialType::Sand:
		{
			m_shape.setFillColor(sf::Color(255, 255, 0));
			break;
		}
		case MaterialType::Water:
		{
			m_shape.setFillColor(sf::Color(0, 0, 255));
			break;
		}
		case MaterialType::Stone:
		{
			m_shape.setFillColor(sf::Color(115, 115, 115));
			break;
		}
		case MaterialType::Metal:
		{
			m_shape.setFillColor(sf::Color(55, 55, 55));
			break;
		}
		case MaterialType::Steam:
		{
			m_shape.setFillColor(sf::Color(215, 215, 215));
			break;
		}
		case MaterialType::Ground:
		{
			m_shape.setFillColor(sf::Color(73, 29, 0));
			break;
		}
		case MaterialType::Lava:
		{
			m_shape.setFillColor(sf::Color(255, 88, 0));
			break;
		}
		default:
		{
			m_shape.setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
}
